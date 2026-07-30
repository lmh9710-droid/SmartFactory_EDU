import streamlit as st

from src import queries, services, ui

with st.form("설계품목 등록"):
    st.subheader("설계품목 등록")
    item_id : int = st.number_input(label="ID", value=0, min_value=0)
    item_code : str = st.text_input(label="품목코드")
    item_name : str = st.text_input(label="품목명")
    item_type : str = st.selectbox(label="품목타입", options=["PRODUCT", "MATERIAL"])
    unit : str = st.selectbox(label="단위",options=['EA', 'KG'])
    is_active : str = st.selectbox(label="사용여부",options=["Y", "N"])
    submitted = st.form_submit_button(label="등록")


if submitted:
    data = services.itemRegistration(
        item_id=item_id,
        item_code=item_code,
        item_name=item_name,
        item_type=item_type,
        unit= unit,
        is_active=is_active
    )

    try: 
        result = services.register_item(data)
    

    except ValueError as exc:
            st.error(str(exc))  

st.subheader("Item 조회")

df=queries.items()

ui.show_dataframe(df)

