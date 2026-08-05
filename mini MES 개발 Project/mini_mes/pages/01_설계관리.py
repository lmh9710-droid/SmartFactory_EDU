import streamlit as st

from src import queries, services, ui

st.title("설계관리 시스템")
st.divider()

col_input, col_view = st.columns([1, 1])


with col_input:
  tab1, tab2 = st.tabs(["품목등록", "단종여부 업데이트"])
  with tab1:
    with st.form("설계품목 등록"):
        st.subheader("설계품목 등록")
        st.divider()
        item_code : str = st.text_input(label="품목코드")
        item_name : str = st.text_input(label="품목명")
        item_type : str = st.selectbox(label="품목타입", options=["PRODUCT", "MATERIAL"])
        unit : str = st.selectbox(label="단위",options=['EA', 'KG'])
        is_active : str = st.selectbox(label="사용여부",options=["Y", "N"])
        submitted = st.form_submit_button(label="등록")


    if submitted:
        data = services.itemRegistration(
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

  with tab2: 

    with st.form("사용 업데이트"):
        st.subheader("품목 단종여부 업데이트")
        st.divider()
        item_id : int = st.number_input(label="ID", value=0, min_value=0)
        is_active : str = st.selectbox(label="사용여부",options=['Y', 'N'])
        submitted = st.form_submit_button(label="등록")

    if submitted:
        try:
            result = queries.item_active_update(is_active = is_active, item_id = item_id)
            st.write(result)

        except ValueError as exc:
                st.error(str(exc)) 



with col_view:

    df=queries.items()
    item_type=queries.item_type_counts()

    if not df.empty:
      st.subheader("Item 조회")
      ui.show_dataframe(df) 
    if not item_type.empty:
      st.subheader("Item 등록 현황")
      st.bar_chart(item_type.set_index("item_type")["item_count"])
      

