import streamlit as st 

from datetime import date, timedelta

from src import queries, ui, services

st.title("생산실적")

ui.setup_page("생산실적 조회")


# col1, col2, col3 = st.columns(3)
# keyword = col1.text_input("생산번호, 품목명, 완제품 LOT 검색")
# use_data_filter = col2.checkbox("생산일자 필터 사용 ")

# date_from = None
# date_to = None

# if use_data_filter:
#     date_from = col2.date_input("시작일")
#     date_to = col3.date_input('종료일')

# df = queries.productions(keyword=keyword, date_from = date_from, date_to = date_to)

tab1, tab2 = st.tabs(["생산실적 조회", "생산완료 등록"])

with tab1:
 col1, col2, col3 = st.columns(3)
 keyword = col1.text_input("생산번호, 품목명, 완제품 LOT 검색")
 use_data_filter = col2.checkbox("생산일자 필터 사용 ")

 date_from = None 
 date_to = None
 df = queries.productions(keyword=keyword, date_from = date_from, date_to = date_to)

 if use_data_filter:
    date_from = col2.date_input("시작일")
    date_to = col3.date_input('종료일')

 df = queries.productions(keyword=keyword, date_from = date_from, date_to = date_to)

 if not df.empty:
    ui.metric_row(
        [
            ("생산실적 수", len(df)),
            ("총 생산수량", f"{df['production_qty'].sum():,.0f}"),
            ("완제품 LOT 수", df["output_lot_no"].nunique()),
        ]
    )


 st.subheader("생산 이벤트와 결과 LOT")
 ui.show_dataframe(df)


with tab2:

    products = queries.active_items_for_select("PRODUCT")
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

    with st.form("production_form"):
        product_label = st.selectbox("생산할 완제품 품목", list(product_option.keys()) )
        production_date = st.date_input("생산일자", value=date.today())
        production_no = st.text_input("생산번호", value=f"PRD-{date.today().strftime('%Y%m%d')}-NEW")
        output_lot_no = st.text_input("생성할 완제품 LOT 번호", value=f"FG-NEW-{date.today().strftime('%Y%m%d')}-001")
        qty = st.number_input("생산수량", min_value=0.0, value=1000.0, step=100.0)
        expire_date = st.date_input("완제품 유효기간", value=date.today()+timedelta(days= 180))

        st.subheader("투입 원자재")
        selected_material_labels = st.multiselect(
            "원자재 LOT 선택",
            list(material_options.keys()),
            default = list(material_options.keys())[:3],
        )
        

        material_rows = []
        for label in selected_material_labels:
            lot = material_options[label]
            used_qty = st.number_input(
                f"{lot['lot_no']} 투입수량",
                min_value= 0.0,
                value= float(qty),
                step =100.0,
                key=f"material_qty_{lot['lot_id']}",

            )
            material_rows.append(
                {
                    "material_item_id" : lot["item_id"],
                    "material_lot_id" : lot["lot_id"],
                    "qty": used_qty,   
                }
            )

        submitted = st.form_submit_button("생산실적 저장")

    if submitted:
        data = services.ProductionRegistration(
            product_item_id = product_option[product_label],
            output_lot_no = output_lot_no,
            production_no = production_no,
            production_date= production_date,
            qty=qty,
            expire_date=expire_date,
            material_rows=material_rows

        )

        try:
            result = services.register_production(data)
            st.success("생산실적이 정상적으로 등록되었습니다.")
            st.write(result)
            st.info(
                """
                저장된 직업:
                1. 완제품 LOT 1건 생성
                2. 생산실적 1건 생성 
                3. 선택한 원자재 LOT 별 투입 이력 생성 
                """
            )

        except ValueError as exc:
            st.error(str(exc))