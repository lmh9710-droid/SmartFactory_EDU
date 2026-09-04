import streamlit as st
import pandas as pd
import sqlite3
import plotly.express as px

# 💡 2초마다 대시보드 화면 전체를 자동으로 새로고침 (C++ 미들웨어와 실시간 동기화)
from streamlit_autorefresh import st_autorefresh
st_autorefresh(interval=2000, key="factory_datarefresh")

DB_PATH = r"C:\App\src\db\sensor_data.db"

def get_connection():
    return sqlite3.connect(DB_PATH)

# =========================================================================
# 🏭 SIDEBAR : 스마트 팩토리 중앙 제어 판넬 스타일
# =========================================================================
st.sidebar.title("🏭 SMART FACTORY OEE")
st.sidebar.markdown("### 🎛️ 중앙 관제 시스템")

menu = st.sidebar.radio(
    "📊 모니터링 가동 라인",
    ["설비 1번 (온습도 가공 라인)", "설비 2번 (광도 제어 라인)"]
)

st.sidebar.markdown("---")
st.sidebar.subheader("🌐 시스템 연결 상태")
st.sidebar.success("● C++ Middleware: ONLINE")
st.sidebar.success("● SQLite3 Engine: CONNECTED")

# =========================================================================
# 📊 MAIN PAGE : 실시간 스마트 관제 레이아웃
# =========================================================================

conn = get_connection()

if menu == "설비 1번 (온습도 가공 라인)":
    st.title("🌡️ 설비 1번 - 실시간 온습도 관제 센터")
    st.caption("공정 내부 환경 데이터를 실시간으로 모니터링하고 임계치 이탈을 감시합니다.")

    query = "SELECT id, port_name, temperature, humidity, created_at FROM dht_logs ORDER BY id DESC LIMIT 1"
    df_current = pd.read_sql_query(query, conn)
    
    query_list = "SELECT id, port_name, temperature, humidity, created_at FROM dht_logs ORDER BY id DESC"
    df_history = pd.read_sql_query(query_list, conn) # 전체 이력 데이터 추출
    
    # 💡 [CSV 변환] 현재 보고 있는 테이블을 UTF-8 BOM 인코딩 CSV로 변환 (한글 안 깨짐)
    csv_data = df_history.to_csv(index=False).encode('utf-8-sig')
    file_name = f"dht_sensor_logs_{pd.Timestamp.now().strftime('%Y%m%d_%H%M%S')}.csv"

    if not df_current.empty:
        cur_temp = df_current['temperature'].iloc[0]
        cur_humi = df_current['humidity'].iloc[0]

        # 🚨 임계치 감시 시스템
        temp_threshold = 26.0
        humi_threshold = 54.5
        
        col_status, col_alarm = st.columns(2)
        with col_status:
            st.markdown("#### **라인 가동 상태**")
        with col_alarm:
            if cur_temp >= temp_threshold or cur_humi >= humi_threshold:
                st.error(f"⚠️ [위험] 설비 과열 및 과습 경보! (기준: {temp_threshold}°C / {humi_threshold}%)")
            else:
                st.success("✅ [정상] 설비 가동 환경 안정화 상태")

        st.markdown("---")

        # 대형 Metric 칩 배치
        col1, col2, col3 = st.columns(3)
        col1.metric("현재 온도", f"{cur_temp:.2f} °C", delta=f"{cur_temp - 24.0:.2f}°C (기준대비)")
        col2.metric("현재 습도", f"{cur_humi:.2f} %", delta=f"{cur_humi - 50.0:.2f}% (기준대비)", delta_color="inverse")
        
        avg_temp = df_history['temperature'].head(50).mean() # 최근 50건 평균
        col3.metric("최근 평균 온도", f"{avg_temp:.2f} °C")

        st.markdown("---")

        # 트렌드 차트
        st.subheader("📈 실시간 환경 변화 트렌드")
        df_sorted = df_history.head(50).sort_values('created_at') # 최근 50건 차트 표출
        fig = px.line(df_sorted, x='created_at', y=['temperature', 'humidity'], 
                      title='실시간 온습도 연동 추이',
                      color_discrete_sequence=["#FF4B4B", "#1C83E1"])
        fig.update_layout(hovermode="x unified", legend_title_text='센서')
        st.plotly_chart(fig, use_container_width=True)

    else:
        st.info("아두이노 10번 포트로부터 데이터를 수신 대기 중입니다...")

elif menu == "설비 2번 (광도 제어 라인)":
    st.title("☀️ 설비 2번 - 실시간 조도 통계 및 종합 효율(OEE)")
    st.caption("광도 센서 정수 데이터를 기반으로 공장 라인의 조도 밸런스를 측정합니다.")

    query = "SELECT id, port_name, lux_value, created_at FROM light_logs ORDER BY id DESC"
    df_history = pd.read_sql_query(query, conn) # 전체 이력 데이터 추출
    
    # 💡 [CSV 변환] 현재 보고 있는 테이블을 UTF-8 BOM 인코딩 CSV로 변환 (한글 안 깨짐)
    csv_data = df_history.to_csv(index=False).encode('utf-8-sig')
    file_name = f"light_sensor_logs_{pd.Timestamp.now().strftime('%Y%m%d_%H%M%S')}.csv"

    if not df_history.empty:
        cur_lux = df_history['lux_value'].iloc[0]
        max_lux = df_history['lux_value'].max()
        min_lux = df_history['lux_value'].min()

        col1, col2 = st.columns(2)
        
        with col1:
            st.subheader("🧭 실시간 가동 효율 지표 (OEE)")
            efficiency = min(100.0, (cur_lux / 200.0) * 100) if cur_lux > 0 else 0
            
            st.markdown(f"### **종합 가동률: {efficiency:.1f}%**")
            st.progress(int(efficiency) / 100.0)
            
            if efficiency >= 80:
                st.success("🟢 가동 상태: 최적 (Excellent)")
            elif efficiency >= 50:
                st.warning("🟡 가동 상태: 주의 (Warning)")
            else:
                st.error("🔴 가동 상태: 위험 (Critical)")

        with col2:
            st.markdown("#### **조도 통계 현황**")
            st.write("") 
            st.metric("현재 광도", f"{cur_lux} Lux")
            st.metric("최대 기록", f"{max_lux} Lux")
            st.metric("최소 기록", f"{min_lux} Lux")

        st.markdown("---")

        # 입체적인 Area 차트 시각화
        st.subheader("📊 실시간 조도 스펙트럼 변화")
        df_sorted = df_history.head(50).sort_values('created_at')
        fig_area = px.area(df_sorted, x='created_at', y='lux_value', 
                           title='시간별 조도 트렌드 수집 로그',
                           color_discrete_sequence=["#00D2FC"])
        st.plotly_chart(fig_area, use_container_width=True)
        
    else:
        st.info("아두이노 12번 포트로부터 데이터를 수신 대기 중입니다...")

conn.close()

# 💡 [사이드바 하단 배치] 현재 활성화된 설비의 전체 데이터를 CSV로 다운로드하는 버튼
st.sidebar.markdown("---")
st.sidebar.subheader("💾 공정 데이터 백업")
st.sidebar.download_button(
    label="📥 현재 설비 CSV 다운로드",
    data=csv_data,
    file_name=file_name,
    mime="text/csv"
)
st.sidebar.caption("※ 클릭 시 현재 가동 라인의 전체 내역이 CSV 파일로 저장됩니다.")

# =========================================================================
# 📋 FOOTER : 공통 하단 데이터 원본 테이블 표출
# =========================================================================
st.markdown("---")
st.subheader("💾 데이터베이스 저장 현황 (최근 5개 행)")
conn = get_connection()
if menu == "설비 1번 (온습도 가공 라인)":
    df_raw = pd.read_sql_query("SELECT * FROM dht_logs ORDER BY id DESC LIMIT 5", conn)
else:
    df_raw = pd.read_sql_query("SELECT * FROM light_logs ORDER BY id DESC LIMIT 5", conn)
conn.close()
st.dataframe(df_raw, use_container_width=True)
