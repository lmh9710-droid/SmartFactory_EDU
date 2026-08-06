import streamlit as st 

from datetime import date, timedelta

from src import queries, ui, services

st.title("출하관리")
st.divider()

col1, col2, col3 = st.columns(3)
keyword = col1.text_input("생산번호, 품목명, 완제품 LOT 검색")
use_data_filter = col2.checkbox("생산일자 필터 사용 ")

date_from = None
date_to = None

if use_data_filter:
    date_from = col2.date_input("시작일")
    date_to = col3.date_input('종료일')

df = queries.productions(keyword=keyword, date_from = date_from, date_to = date_to)


tab1, tab2 = st.tabs(["출하전 LOT","출하완료 LOT"])


with tab1:
    st.subheader("출하가능 LOT")
    before_shipping_df = df[df['status']=='COMPLETED']
    ui.show_dataframe(before_shipping_df)

with tab2:
    st.subheader("출하완료 LOT")
    after_shipping_df=df[df['status']=='SHIPPED']
    ui.show_dataframe(after_shipping_df)

shipable_lots = queries.status_items_for_select()

if not shipable_lots:
      st.warning("생산 등록에 필요한 제품 품목 또는 원자재 LOT가 없습니다.")
      st.stop

shipable_options = {
     f"{lot['lot_no']}|{lot['item_name']}|{lot['qty']: ,.0f}" : lot['lot_id']
     for lot in shipable_lots
}

with st.form("shipping"):
    selected_ship_label = st.selectbox(
         label = "출하 LOT 선택",
         options = list(shipable_options.keys()),
    )
    submitted  = st.form_submit_button(label="출하등록")

if submitted:
   queries.status_update(status="SHIPPED", lot_id= shipable_options[selected_ship_label])
   st.rerun()