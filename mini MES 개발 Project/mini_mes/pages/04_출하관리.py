import streamlit as st 

from datetime import date, timedelta

from src import queries, ui, services

col1, col2, col3 = st.columns(3)
keyword = col1.text_input("생산번호, 품목명, 완제품 LOT 검색")
use_data_filter = col2.checkbox("생산일자 필터 사용 ")

date_from = None
date_to = None

if use_data_filter:
    date_from = col2.date_input("시작일")
    date_to = col3.date_input('종료일')

df = queries.productions(keyword=keyword, date_from = date_from, date_to = date_to)

st.subheader("출하가능 LOT")
ui.show_dataframe(df)

shipable_lots = queries.lots_for_select(lot_type="PRODUCTION")

if not shipable_lots:
      st.warning("생산 등록에 필요한 제품 품목 또는 원자재 LOT가 없습니다.")
      st.stop

shipable_options = {
     f"{lot['lot_no']}|{lot['item_name']}|{lot['qty']: ,.0f}" : lot['lot_id']
     for lot in shipable_lots
}

with st.form("shipping"):
    shipable_date = st.date_input("출하일자", value=date.today())
    selected_ship_label = st.selectbox(
         label = "출하 LOT 선택",
         options = list(shipable_options.keys()),
    )
    submitted  = st.form_submit_button(label="출하등록")

if submitted:
   queries.received_date_update(received_date=shipable_date, 
                               lot_id=shipable_options[selected_ship_label])
