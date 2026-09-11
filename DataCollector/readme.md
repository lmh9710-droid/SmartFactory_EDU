# 멀티스레드 기반 센서 데이터 수집을 통한 MES 기능 확장

## 1. 프로젝트 개요

1. **임베디드 센서 제어:** 임베디드 하드웨어의 센서 제어 펌웨어 로직 구현
2. **미들웨어 데이터 적재:** UART 통신으로 수신한 센서 데이터를 PC 환경에서 Read하여 데이터베이스(SQLite)에 저장
3. **실시간 모니터링:** SQLite에 저장된 센서 계측 데이터를 웹 대시보드(Streamlit)를 통해 실시간 시각화

---

## 2. 사용 장비 및 부품

| 구분 | 항목 | 세부 스펙 및 설명 |
| :--- | :--- | :--- |
| **Processor** | R7FA4M1AB3CFM | Renesas 32-bit ARM® Cortex®-M4 |
| | ATmega328P | Microchip 8-bit AVR® |
| **Sensor** | DHS Sensor | 디지털 온습도 센서 |
| | CDS Sensor | 조도(광도) 센서 |
| **Cable** | USB Cable | USB Type-C / USB A to B |

---

## 3. 개발 환경

* **임베디드 하드웨어 (임시 설비)**
  * **Role:** 센서 데이터 계측 및 UART 통신 기반 PC 데이터 송출
  * **Language:** `C`, `C++`
* **MiddleWare (데이터 수집기)**
  * **Role:** UART 시리얼 데이터를 수신하여 SQLite DB에 비동기/멀티스레드 적재
  * **Language:** `C++`
* **Dashboard**
  * **Role:** DB 데이터 시각화 및 공정별 모니터링 UI 구현
  * **Language / Framework:** `Python`, `Streamlit`

---

## 4. Work Process

### 1) 임베디드 펌웨어 로직 구현
* 2대의 임베디드 보드를 **[온습도 공정]**과 **[광도 측정 공정]**으로 역할 분담
* 각 센서 모듈 핀 맵 매핑 및 주기적 데이터 샘플링 펌웨어 로직 작성

### 2) Middleware (C++ 데이터 수집기) 구조 설계
* **클래스 설계:** Base Class로 `DataBase` 및 `SensorReader` 추상화
* **다형성 활용:** 조도/온습도 전용 자식 클래스 정의 및 인터페이스 오버라이딩(Overriding) 구현
* **멀티스레딩:** `main` 프로세스에서 각 공정(UART 채널)을 별도 Thread로 분리하여 병렬 수집 처리

### 3) Dashboard (Streamlit) 구축
* Sidebar 메뉴를 통한 **공정 1(온습도) / 공정 2(조도)** 선택 인터페이스 제공
* 실시간 센서 계측치 트렌드 차트 및 상태 모니터링 화면 구성

---

## 5. 시스템 구조 (Class Diagram)

<img width="1398" height="563" alt="Class Diagram" src="https://github.com/user-attachments/assets/73ff1b65-36d8-4183-9a72-ec557bad8bfe" />

---

## 6. 실습 및 동작 확인 사진

### 1) 임베디드 하드웨어 구성
<img width="485" height="364" alt="Embedded Hardware" src="https://github.com/user-attachments/assets/55aa8bb2-5f22-49ae-bfea-6f084f8f3713" />

### 2) C++ 미들웨어 데이터 통신 동작
<img width="358" height="624" alt="Middleware Communication" src="https://github.com/user-attachments/assets/1f7ef04d-4645-4915-b9c4-2c2bb1954d5f" />

### 3) 공정 1번 (Thread 1) 모니터링
<img width="962" height="1027" alt="Thread 1 Monitoring" src="https://github.com/user-attachments/assets/6e297107-1137-4d3f-b214-6c4a4192dcbd" />

### 4) 공정 2번 (Thread 2) 모니터링
<img width="957" height="1035" alt="Thread 2 Monitoring" src="https://github.com/user-attachments/assets/aae84e5f-cd3b-4e95-b5c5-772c39dd457d" />

