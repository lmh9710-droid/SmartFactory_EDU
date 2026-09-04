

# 프로젝트명: 데이터 수집 with Arduino

## 1. 프로젝트 개요 
### 1)Arduino 보드를 사용하여 Sensor 제어 로직 작성
### 2)Arduino 발생하는 센서 값을 UART 통신으로 Read하여 DataBase(SQLite)에 저장하는 프로그램 작성 
### 3)DataBase(SQLite)에 저장된 센서값을 Dash Board(streamlit) 화면위에 통계분석 환경 구축
  
---
## 2. 개발환경
### 1)하드웨어/ 설비 -  Arduino
- 기능: 센서값 Read하여 UART 통신으로 PC에 출력
- 개발언어: C/C++
### 2)Middle Ware(데이터 수집기)
- 기능: Arduino로 부터 발행된 센서값을 Read하여 DataBase(SQLite) 저장 
- 개발언어: C++
### 3)DashBoard(streamlit) 
- 기능: 모니터링 환경
- 개발언어: Python

---
## 3. Work Process
### 1)Arduino 펌웨어 로직 프로그램 작성
- Arduino Board 2개 사용하여 1대 온습도 ccmrwjd 공정, 1대 광도측정 공정으로 사용
- 각 센서 부품들을 보드에 연결하여 센서 제어하는 프로그램 로직 작성
### 2)Middle Ware(데이터 수집기) 프로그램 작성
- 부모 개체 DataBase, SensorReader 설계 및 프로그램 작성
- 조도, 온습도 정보를 Read하고 DataBase(SQlite) 저장할수있는 자식 개체 및 함수 오버로딩 설계 및 로직 작성
- main 함수에 2공정을 각 thread로 나누어서 동작하게 하는 로직 작성후, 빌드  
### 3)Dashboard(streamlit) 스크립트 작성
- 조도, 온습도 공정을 각각 좌측 사이드 바에 표시
- 공정별 센서 계측치 모니터링
  
---
## 4. Class Diagram
<img width="940" height="516" alt="image" src="https://github.com/user-attachments/assets/90eb5d9e-38a8-4aa2-9abb-894a3ebcc52b" />

---
## 5. 실습사진
### 1)공정 1번(thread1) 모니터링

<img width="962" height="1027" alt="Screenshot_6" src="https://github.com/user-attachments/assets/6e297107-1137-4d3f-b214-6c4a4192dcbd" />

### 2)공정 2번(thread2) 모니터링 

<img width="957" height="1035" alt="Screenshot_7" src="https://github.com/user-attachments/assets/aae84e5f-cd3b-4e95-b5c5-772c39dd457d" />

### 3)미들웨어(C++) 콘솔창 동작확인

<img width="358" height="624" alt="Screenshot_8" src="https://github.com/user-attachments/assets/1f7ef04d-4645-4915-b9c4-2c2bb1954d5f" />
