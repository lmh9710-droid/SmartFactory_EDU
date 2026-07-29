import streamlit as st 
import sqlite3
from src import queries, ui

conn = sqlite3.connect("./sql/mini_mes.db")
ui.setup_page("MES-Manufacture Execution Sysmtem")

ui.page_title(
    "MES System",
    "오늘 종말이어도 공장은 돌아간다.",
    "매출 1000억 가즈아 ~!",
    "안전 제일!!!!"
)


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

ui.show_database_status()

