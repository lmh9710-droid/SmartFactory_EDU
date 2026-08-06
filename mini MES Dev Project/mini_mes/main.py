import streamlit as st 
import sqlite3
from src import queries, ui


conn = sqlite3.connect("./sql/mini_mes.db")



ui.setup_page("MES-Manufacture Execution Sysmtem")
st.title("MINI MES")

st.divider()

try:
    counts = queries.table_counts()
    count_map = dict(zip(counts["table_name"], counts["row_count"]))
    ui.metric_row(
        [
            ("품목 수", count_map.get("item", 0)),
            ("LOT 수", count_map.get("lot", 0)),
            ("생산실적 수", count_map.get("production", 0)),
            ("원자재 투입 행 수", count_map.get("production_material", 0)),
        ]
    )
except Exception as exc:
    st.error("데이터베이스 구조를 확인하는 중 오류가 발생했습니다.")
    st.exception(exc)

st.divider()


#------------------ 일자별 생산, 불량 흐름 -------------------------------    
extra1, extra2 = st.columns(2)
prod_date = queries.production_by_date()
defect_date = queries.defect_by_date()

with extra1:
    st.subheader("일자별 생산 흐름")
    if not prod_date.empty:
     st.line_chart(prod_date.set_index("production_date")["production_qty"], height= 260)

with extra2:
   defect_date = queries.defect_by_date()
   st.subheader("일자별 불량 흐름")
   if not defect_date.empty:
      st.area_chart(defect_date.set_index("produced_date")["defect_qty"], height = 260)
#-----------------------------------------------------------

st.subheader("항목별 불량수")
df1 = queries.defect_item()
detail = df1.groupby('defect_detail', as_index = False)['defect_qty'].sum()
st.bar_chart(data = detail, x="defect_detail", y="defect_qty",color="#FF4B4B")

#---------------------------------------------------------

df = queries.productions()
st.subheader("생산완료")
ui.show_dataframe(df)

ui.show_database_status()