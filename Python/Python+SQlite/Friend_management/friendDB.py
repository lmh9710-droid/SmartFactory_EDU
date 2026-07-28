import sqlite3 


class Database: 
    # DB 연결 정보와 초기화 작업을 관리한다.
    def __init__(self, db_path):
        self.db_path = db_path
    
    def connect(self):
        conn = sqlite3.connect(self.db_path)
        return conn
    
    def init_db(self):
        with self.connect() as conn:
            conn.executescript("""
            create table IF NOT EXISTS friend
            (
              friend_id integer primary key autoincrement,
              friend_name text
            )                  
            """)
    
    def add_friend(self, friend_name):
        with self.connect() as conn:
            conn.execute("""
            insert into friend (friend_name)
            values(?)""",(friend_name,))
        
    def find_friend(self):
        with self.connect() as conn:
            cur = conn.execute("""
            Select
            friend_id, friend_name
            from friend
            """)
        return cur.fetchall()
    
    def update_friend(self, friend_name, friend_id):
        with self.connect() as conn:
            conn.execute("""
            update friend
            set friend_name = ?
            where friend_id = ?                 
            """, (friend_name, friend_id))
    
    def delete_friend(self,friend_id):
        with self.connect() as conn:
            conn.execute("""
            delete from friend 
            where friend_id = ?
                         """,(friend_id,))
        
     
