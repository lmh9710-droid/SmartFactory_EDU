# [shop_crud_simple.py]
import sqlite3

# 1. DB 및 테이블 초기화
def init_db(db_name="shop.db"):
    # 연결 객체를 conn 변수에 직접 대입
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    # 외래 키 활성화 및 테이블 생성
    cursor.execute("PRAGMA foreign_keys = ON;")
    
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS Customers (
        customer_id INTEGER PRIMARY KEY,
        name TEXT NOT NULL,
        email TEXT UNIQUE
    );
    """)
    
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS Orders (
        order_id INTEGER PRIMARY KEY,
        customer_id INTEGER NOT NULL,
        order_date TEXT DEFAULT CURRENT_DATE,
        FOREIGN KEY(customer_id) REFERENCES Customers(customer_id)
    );
    """)
    
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS Order_Items (
        item_id INTEGER PRIMARY KEY,
        order_id INTEGER NOT NULL,
        product_name TEXT,
        quantity INTEGER,
        price INTEGER,
        FOREIGN KEY(order_id) REFERENCES Orders(order_id)
    );
    """)
    
    conn.commit()  # 변경 사항 저장
    cursor.close() # 커서 닫기
    conn.close()   # 연결 닫기

# ==========================================
# 2. CREATE (생성)
# ==========================================
def create_customer(db_name, name, email):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    cursor.execute("INSERT INTO Customers (name, email) VALUES (?, ?);", (name, email))
    last_id = cursor.lastrowid  # 변수에 ID 대입
    
    conn.commit()
    cursor.close()
    conn.close()
    return last_id

def create_order(db_name, customer_id):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    cursor.execute("INSERT INTO Orders (customer_id) VALUES (?);", (customer_id,))
    last_id = cursor.lastrowid
    
    conn.commit()
    cursor.close()
    conn.close()
    return last_id

def create_order_item(db_name, order_id, product_name, quantity, price):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    cursor.execute(
        "INSERT INTO Order_Items (order_id, product_name, quantity, price) VALUES (?, ?, ?, ?);",
        (order_id, product_name, quantity, price)
    )
    last_id = cursor.lastrowid
    
    conn.commit()
    cursor.close()
    conn.close()
    return last_id

# ==========================================
# 3. READ (조회)
# ==========================================
def get_customer_orders(db_name):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    query = """
    SELECT c.name, o.order_id, o.order_date, oi.product_name, oi.quantity, oi.price
    FROM Customers c
    JOIN Orders o ON c.customer_id = o.customer_id
    JOIN Order_Items oi ON o.order_id = oi.order_id;
    """
    cursor.execute(query)
    records = cursor.fetchall()  # 결과를 변수에 대입
    
    cursor.close()
    conn.close()
    return records

# ==========================================
# 4. UPDATE (수정)
# ==========================================
def update_customer_email(db_name, customer_id, new_email):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    cursor.execute("UPDATE Customers SET email = ? WHERE customer_id = ?;", (new_email, customer_id))
    
    conn.commit()
    cursor.close()
    conn.close()

# ==========================================
# 5. DELETE (삭제)
# ==========================================
def delete_order_item(db_name, item_id):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    cursor.execute("DELETE FROM Order_Items WHERE item_id = ?;", (item_id,))
    
    conn.commit()
    cursor.close()
    conn.close()

