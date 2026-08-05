import streamlit as st

from src import queries, services, ui

st.title("BOM 추적")
st.divider()

tab1, tab2 = st.tabs(["정방향 추적", "역방향 추적"])

with tab1:
    material_lots = queries.lots_for_select("RECEIPT")
    if not material_lots:
        st.warning("원자재 LOT가 없습니다.")
        st.stop()

    options ={
        f"{lot['lot_no']}|{lot['item_name']}|보유{lot['qty']:,.0f}" : lot["lot_id"]
        for lot in material_lots
    }

    selected_label = st.selectbox(label= "원자재 LOT",options= list(options.keys()))

    df= queries.forward_trace(options[selected_label])

    st.subheader("추적 결과")
    ui.show_dataframe(df, "원자재 LOT를 사용한 생산실적이 없습니다.")

with tab2:
    output_lots = queries.lots_for_select("PRODUCTION")
    if not output_lots:
        st.warning("제품 LOT가 없습니다.")
        st.stop()

    options= {
        f"{lot['lot_no']}|{lot['item_name']}|보유{lot['qty']:,.0f}" : lot["lot_id"]
        for lot in output_lots
    }

    selected_label = st.selectbox(label= "제품 LOT", options = list(options.keys()))

    df= queries.reverse_trace(options[selected_label])

    st.subheader("추적결과")
    ui.show_dataframe(df, "제품 LOT를 생산실적이 없습니다. ")

