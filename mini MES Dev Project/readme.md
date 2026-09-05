
# 프로젝트명: mini MES 개발 Project

## 1. 프로젝트 개요 
- 해당 프로젝트는 라면제조 공정 MES 개발 프로젝트 입니다.
- 기안자: 이민하
  
---

## 2. 개발 목적 
- 관리 전산화 및 자동화
- 비용절감 CI(Cost Inovation)
- 품질개선 위한 데이터 확보

---

## 3. 대상 사용자
- 생산관리 담당자 → 생산실적 관리
- 자재 구매 담당자 → 부품 구매, 재고 관리
- 품질 담당자 → 품질검사 관리
- 영업 담당자 → 출하 관리
- 설계 담당자 → 설계 Item 등록 및 관리 
  
---

## 4. 주요기능 
### 1)설계 관리
- 설계 ITEM 등록
- 단종여부 업데이트
### 2)자재관리
- 자재 구매품 입고 등록
### 3)품질검사
- IQC(input quality control) 검사 판정
### 4)생산실적
- 생산실적 조회
- 생산완료 등록
### 5)출하관리
- 출하 등록
- 출하 이력 조회
### 6)BOM 추적
- 정방향 추적
- 역방향 추적 

---

## 5. 개발환경
### 1) Data Base 
- 기능: Raw 데이터 저장 
- 개발언어: SQL(SQLITE)
### 2) Web 모니터링(streamlit)
- 기능: 데이터 등록, 조회, 업데이트
- 개발언어: Python

---

## 6. DATABASE Modeling
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
