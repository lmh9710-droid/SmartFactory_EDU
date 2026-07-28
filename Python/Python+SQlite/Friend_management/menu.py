import friendDB as fb


class menuDisplay:
 
 def __init__(self, db_path):
  self.db = fb.Database(db_path)
  self.db.init_db()
  
 
 def print_menu(self):
  print("""
   ================
   1. 친구 리스트 출력
   2. 친구 추가
   3. 친구 삭제
   4. 이름변경
   9. 종료      """)
  
 def run(self):
  choice = input("메뉴를 선택하시오.")

  if choice =='1':
   rows= self.db.find_friend()
   print("\n[친구 목록]")
   for row in rows:
     print(row)

  elif choice =='2':
   name = input("이름을 입력: ")
   self.db.add_friend(name)
  elif choice =='3':
   id = int(input("삭제할 ID: "))
   self.db.delete_friend(id) 
  elif choice =='4':
   id= int(input("업데이트할 ID 입력: "))
   name = input("업데이트할 이름을 입력: ")
   self.db.update_friend(name, id)
  elif choice == '9':
   print("프로그램 종료")
   return 0
  else:
   print("잘못된 메뉴")
   