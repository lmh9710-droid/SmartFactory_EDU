

# 프로젝트명: 데이터 수집 with Arduino

## 1. 프로젝트 개요 
- Arduino 발생하는 센서 값을 UART 통신으로 Read하여 DataBase(SQLite)에 저장하는 프로그램 작성 
- DB(SQLite)에 저장된 센서값을 Dash Board(streamlit) 화면위에 통계분석 환경 구축
  
---

## 2. Work Process
### 1)Arduino 펌웨어 로직 프로그램 작성
### 2)Middle Ware(데이터 수집기) 프로그램 작성
### 3)Dashboard(streamlit) 스크립트 작성


---

## 3. 개발환경
### 1) 하드웨어/ 설비 -  Arduino
- 기능: 센서값 Read하여 UART 통신으로 PC 출력
- 개발언어: C/C++
### 2) Middle Ware(데이터 수집기)
- 기능: Arduino로 부터 발해된 센서값을 Read하여 DataBase(SQLite) 저장 
- 개발언어: C++
### 3) DashBoard(streamlit) 
- 기능: 통계분석 환경
- 개발언어: Python

---
