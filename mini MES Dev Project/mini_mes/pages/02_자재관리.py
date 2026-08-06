import streamlit as st 

from datetime import date, timedelta

from src import queries, ui, services

st.title("자재관리")
st.divider()

# type_counts = queries.item_type_counts()
# if not type_counts.empty:
#         count_map = dict(zip(type_counts["item_type"], type_counts["item_count"]))
#         ui.metric_row(
#             [
#                 ("전체 품목", int(type_counts["item_count"].sum())),
#                 ("원자재", count_map.get("MATERIAL", 0)),
#             ]
#         )

lots = queries.lots(lot_type='RECEIPT')
if not lots.empty:
    ui.metric_row(
        [
            ("조회 LOT", len(lots)),
            ("현재고 합계", f"{lots['qty'].sum(): ,.0f}"),
            ("품목 수", lots["item_name"].nunique()),
        ]
    )
st.divider()

col_input, col_view = st.columns([1, 2])

# 부품입고 등록
with col_input: 

    products = queries.active_items_for_select("MATERIAL")
    material_lots = queries.lots_for_select("RECEIPT")

    if not products or not material_lots:
        st.warning("생산 등록에 필요한 제품 품목 또는 원자재 LOT가 없습니다.")
        st.stop


    product_option = {
        f"{item['item_code']} | {item['item_name']}":item["item_id"]
        for item in products
    }

    material_options = {
        f"{lot['lot_no']}|{lot['item_name']} | 보유 {lot['qty']: ,.0f}" :lot
        for lot in material_lots
    }

    with st.form("Material_form"):
        st.subheader("입고 등록")
        product_label = st.selectbox(label= "입고 품목", options= list(product_option.keys()) )
        received_date = st.date_input(label= "입고 일자", value=date.today())
        receipt_lot_no = st.text_input(label= "생성할 입고품 LOT 번호", value=f"RM-NEW-{date.today().strftime('%Y%m%d')}-001")
        qty = st.number_input(label="입고수량", min_value=0.0, value=1000.0, step=100.0)
        expire_date = st.date_input(label= "완제품 유효기간", value=date.today()+timedelta(days= 180))

        submitted = st.form_submit_button(label="입고품 등록")

    if submitted:
        data = services.MaterialReceipt(
            lot_no = receipt_lot_no,
            item_id= product_option[product_label],
            qty=qty,
            received_date= received_date,
            expire_date=expire_date,
        )

        try:
            result = services.receive_material(data)
            st.success("생산실적이 정상적으로 등록되었습니다.")
            st.write(result)
            st.info(
                """
                저장된 직업:
                입고 LOT 1건 생성
                """
            )
            st.rerun() 
        except ValueError as exc:
            st.error(str(exc))

#부품 조회
with col_view:
  keyword = st.text_input("품목 검색")
  lot_type =  "RECEIPT"

  with st.form("조회"):
    st.subheader("조회 결과")
    df = queries.lots(keyword=keyword, lot_type= lot_type)
    ui.show_dataframe(df)

