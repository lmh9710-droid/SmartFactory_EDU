
# 프로젝트명: mini MES 개발 Project

## 1. 프로젝트 개요 
- 해당 프로젝트는 라면제조 공정 MES 도입 위한 개발 프로젝트 입니다.
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
### 2) 프론트 엔드 
- 기능: 데이터 조회 및 등록
- 개발언어: Python(streamlit)

---
# Work Porcess

# 1. DATABASE Modeling
## 1)Table Diagram
- item (아이템 정보 테이블)
- lot (LOT 정보 테이블)
- production (제품 생산정보 테이블)
- production_material (재료 생산정보 테이블)
- defect_item (불량품 정보 테이블)
- defect_category (불량 세부 분류 테이블)
<img width="959" height="741" alt="image" src="https://github.com/user-attachments/assets/c53ab38e-c9d8-4b61-b475-42ee93983243" />



## 2)사용된 Query
```
CREATE TABLE item (
    item_id INTEGER PRIMARY KEY,
    item_code TEXT NOT NULL UNIQUE,
    item_name TEXT NOT NULL,
    item_type TEXT NOT NULL CHECK (item_type IN ('PRODUCT', 'MATERIAL')),
    unit TEXT NOT NULL,
    is_active TEXT NOT NULL DEFAULT 'Y' CHECK (is_active IN ('Y', 'N'))
);

CREATE TABLE lot (
    lot_id INTEGER PRIMARY KEY,
    lot_no TEXT NOT NULL UNIQUE,
    item_id INTEGER NOT NULL,
    lot_type TEXT NOT NULL CHECK (lot_type IN ('RECEIPT', 'PRODUCTION')),
    qty REAL NOT NULL CHECK (qty >= 0),
    received_date TEXT,
    produced_date TEXT,
    expire_date TEXT,
    FOREIGN KEY (item_id) REFERENCES item (item_id)
);

CREATE TABLE production (
    production_id INTEGER PRIMARY KEY,
    production_no TEXT NOT NULL UNIQUE,
    item_id INTEGER NOT NULL,
    output_lot_id INTEGER NOT NULL UNIQUE,
    production_date TEXT NOT NULL,
    qty REAL NOT NULL CHECK (qty > 0),
    status TEXT NOT NULL CHECK (status IN ('PLANNED', 'COMPLETED', 'CANCELED','SHIPPED')),
    FOREIGN KEY (item_id) REFERENCES item (item_id),
    FOREIGN KEY (output_lot_id) REFERENCES lot (lot_id)
);

CREATE TABLE production_material (
    production_material_id INTEGER PRIMARY KEY,
    production_id INTEGER NOT NULL,
    material_item_id INTEGER NOT NULL,
    material_lot_id INTEGER NOT NULL,
    qty REAL NOT NULL CHECK (qty > 0),
    FOREIGN KEY (production_id) REFERENCES production (production_id),
    FOREIGN KEY (material_item_id) REFERENCES item (item_id),
    FOREIGN KEY (material_lot_id) REFERENCES lot (lot_id)
);

CREATE TABLE defect_item (
   defect_id INTEGER PRIMARY KEY,
   lot_id INTEGER NOT NULL,
   category_id INTEGER NOT NULL,
   defect_qty real,
   FOREIGN KEY (lot_id) REFERENCES lot (lot_id),
   FOREIGN KEY (category_id) REFERENCES defect_category (category_id)
);

CREATE TABLE defect_category (
   category_id INTEGER PRIMARY KEY,
   defect_detail TEXT NOT NULL UNIQUE
);

```
# 2.프로젝트 구조 
## 1)파일구성 
```
mini_mes/
    main.py
    pages/
        01_설계관리.py
        02_재고관리.py
        03_품질검사.py
        04_생산실적.py
        05_출하관리.py
        06_BOM추적.py
    src/
        db.py
        queries.py
        services.py
        ui.py
    sql/
        mini_mes.db
```
- main.py 시작화면
- pages 부서별 메뉴창 폴더 
- src DB제어 및 SQL함수 폴더 
- sql DB(mini_mes) 폴더

## 2)세부내용 
### 설계관리
- 품목명, 품목타입등을 입력 후, ITEM Table에 삽입

### 자재관리
- 설계관리에서 등록된 품목을 Select Box에서 입고시킬 품목 선택
입고등록 클릭시 lot Table 삽입

### 품질검사
- 불량항목 입력 등록시 defect_category Table 삽입(불량 항목 Category화)
이후 SELECT BOX에서 불량 등록할 LOT_no 선택하여 등록 하면 defect_item Table 삽입

### 생산실적
- 생산완료 등록할 ITEM_Name 및 Material 기입후 등록시 제품 LOT번호 LOT Table 삽입
해당 LOT의 Status는 COMPLETED

### 출하등록 
- 출하할 제품 LOT Select Box에서 선택하여 등록시 
 Status 변경 (COMPLETED → SHIPPED)

### BOM 추적 
- BOM 정방향 또는 역방향 추적 가능 

* 발표 PPT:
https://docs.google.com/presentation/d/1DWFiv2iBwZPOoa4d0S6JV9x6Vxt1R4xrvLa518kbNLw/edit?slide=id.p#slide=id.p
