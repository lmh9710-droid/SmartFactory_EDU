import streamlit as st

from src import db, queries, services, ui

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
       st.wirte(result)
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