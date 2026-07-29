import streamlit as st 

from datetime import date, timedelta

from src import queries, ui, services

keyword = st.text_input("품목 코드 또는 품목명 검색")
item_type =  "MATERIAL"

df = queries.items(keyword=keyword, item_type= item_type)
type_counts = queries.item_type_counts()

tab1, tab2 = st.tabs(["재고조회", "부품입고 등록"])

#재고조회
with tab1:

    if not type_counts.empty:
        count_map = dict(zip(type_counts["item_type"], type_counts["item_count"]))
        ui.metric_row(
            [
                ("전체 품목", int(type_counts["item_count"].sum())),
                ("제품", count_map.get("PRODUCT", 0)),
                ("원자재", count_map.get("MATERIAL", 0)),
            ]
        )

    st.subheader("조회 결과")
    ui.show_dataframe(df)

    if not df.empty:
        selected_item = st.selectbox("상세 확인 품목", df["item_name"].tolist())
        selected_row = df[df["item_name"] == selected_item].iloc[0]
        st.write(
            {
                "품목 ID": int(selected_row["item_id"]),
                "품목 코드": selected_row["item_code"],
                "품목 유형": selected_row["item_type"],
                "단위": selected_row["unit"],
                "연결 Lot 수": int(selected_row["lot_count"]),
            }
        )

# 부품입고 등록
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
        product_label = st.selectbox(" 완제품 품목", list(product_option.keys()) )
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

