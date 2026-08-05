import streamlit as st

from src import queries, services, ui

st.title("품질검사")
st.divider()

col_category, col_defect= st.columns([1, 2])

with col_category:


    with st.form("불량항목 등록"):

        st.subheader("불량항목 등록")
        category_id : int = st.number_input("등록할 ID", value=0)
        defect_detail : str = st.text_input("등록할 내용")
        submitted_category = st.form_submit_button("등록")

        st.divider()
        st.subheader("불량항목 조회")
        df1 = queries.defect_category()
        ui.show_dataframe(df1)
        
    if submitted_category:
        data = services.defectCategoryRegistration(
            category_id=category_id,
            defect_detail=defect_detail
        )

        try:
         result = services.register_defectCategory(data)
         st.success("등록성공")
         st.write(result)
         st.info(
            """
            저장된 목록
            1. 목록 ID
            2. 불량 상세내용
            """
         )
         st.rerun()
        except ValueError as exc:
               st.error(str(exc))   

    

with col_defect:
    tab1 , tab2 = st.tabs(["불량조회", "불량 등록" ])

    with tab1:
       df = queries.defect_item()
       ui.show_dataframe(df)



    with tab2:

        lots= queries.lots_for_select()

        categiries = queries.defect_category_for_select()

        lots_option={
            f"{lot['lot_no']}|{lot['item_name']}":lot["lot_id"]
                    for lot in lots
        }

        categiries_option= {
            f"{category['defect_detail']}": category['category_id']
            for category in categiries
        }

    
        with st.form("불량 등록"):
            st.subheader("불량 등록")
            lot_no : str = st.selectbox(label='LOT_ID',options=list(lots_option.keys()) )
            qty : float = st.number_input(label='qty',min_value=0)
            defect_detail : str =st.selectbox(label='Category', options=list(categiries_option.keys()))

            submitted_item = st.form_submit_button(label="등록")

        if submitted_item:
            data=services.defectItemRegistration(
                lot_id=lots_option[lot_no],
                category_id=categiries_option[defect_detail],
                defect_qty=qty
            )

            try:
                result = services.register_defectItem(data)
                st.write(result)
                st.rerun()  

            except ValueError as exc:
                st.error(str(exc))