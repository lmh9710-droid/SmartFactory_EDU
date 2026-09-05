
# 프로젝트명: Mini MES 개발 Project

## 1. 프로젝트 개요 
- 라면제조 도메인 Mini MES 개발

---

## 2. 주요기능 
### 1)설계 관리
- 설계 ITEM 등록
- ITEM 단종여부 업데이트
### 2)자재관리
- 자재 구매품 입고 등록
### 3)품질검사
- 품질 검사후 판정 결과 등록 
### 4)생산실적
- 생산실적 조회
- 생산완료 항목 등록
### 5)출하관리
- 생산완료품 출하 등록
- 출하 이력 조회
### 6)BOM 추적
- BOM 정방향 추적
- BOM 역방향 추적 

---

## 3. 개발환경
### 1) Data Base 
- 기능: Raw 데이터 저장 
- 개발언어: SQL(SQLITE)
### 2) Web 모니터링(streamlit)
- 기능: 데이터 등록, 조회, 업데이트
- 개발언어: Python

---

## 4. DATABASE Modeling
- item (아이템 정보 테이블)
- lot (LOT 정보 테이블)
- production (제품 생산정보 테이블)
- production_material (재료 생산정보 테이블)
- defect_item (불량품 정보 테이블)
- defect_category (불량 세부 분류 테이블)
<img width="959" height="741" alt="image" src="https://github.com/user-attachments/assets/c53ab38e-c9d8-4b61-b475-42ee93983243" />

---
## 발표 PPT:
https://docs.google.com/presentation/d/1DWFiv2iBwZPOoa4d0S6JV9x6Vxt1R4xrvLa518kbNLw/edit?slide=id.p#slide=id.p
