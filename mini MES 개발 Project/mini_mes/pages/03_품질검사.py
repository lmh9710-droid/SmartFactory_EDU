import streamlit as st

from src import queries, services, ui

with st.form("불량항목 등록"):
    st.subheader("불량항목 등록")
    category_id : int = st.number_input("등록할 ID", value=0)
    defect_detail : str = st.text_input("등록할 내용")
    submitted = st.form_submit_button("등록")

if submitted:
    data = services.defectCategoryRegistration(
        category_id=category_id,
        defect_detail=defect_detail
    )

    try:
       result = services.register_defectCategory(data)
       st.success
       st.write(result)
       st.info(
           """
           저장된 목록
           1. 목록 ID
           2. 불량 상세내용
           """
       )
    except ValueError as exc:
        st.error(str(exc))   


df1 = queries.defect_category()

ui.show_dataframe(df1)

tab1 , tab2 = st.tabs(["불량조회", "불량 등록" ])

with tab1:
  df2 = queries.defect_item()
  ui.show_dataframe(df2)


with tab2:

    lots= queries.lots_for_select()

    lots_option={
        f"{lot['lot_id']}":lot["qty"]
                for lot in lots
    }
   
    with st.form("불량 등록"):
        st.subheader("불량 등록")
        defect_id : int = st.number_input(label="ID", value=0, min_value=0)
        lot_id : str = st.selectbox(label='LOT_ID',options=list(lots_option.keys()) )
        qty : float = st.number_input(label='qty',min_value=0, max_value=int(lots_option[lot_id]))
        category_id : int =st.number_input(label='Category', value=0)
        submitted = st.form_submit_button("등록")

    if submitted:
        data=services.defectItemRegistration(
            defect_id=defect_id,
            lot_id=lot_id,
            category_id=category_id,
            defect_qty=defect_id
        )

        try:
            result = services.register_defectItem(data)
            st.write(result)

        except ValueError as exc:
            st.error(str(exc))

    st.rerun()  