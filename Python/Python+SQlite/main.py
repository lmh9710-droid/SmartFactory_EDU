# [main_switch.py]
import CRUD as shop

def show_menu():
    print("\n=== 쇼핑몰 관리 시스템 ===")
    print("1. 고객 등록")
    print("2. 주문 생성")
    print("3. 주문 내역 조회")
    print("4. 고객 이메일 수정")
    print("5. 종료")
    return input("원하는 작업 번호를 선택하세요: ")

if __name__ == "__main__":
    DB_FILE = "switch_shop.db"
    shop.init_db(DB_FILE)  # DB 테이블 초기화
    
    while True:
        choice = show_menu()
        
        # -------------------------------------------------------------
        # 파이썬의 스위치 케이스 (match-case) 문법 적용
        # -------------------------------------------------------------
        match choice:
            case "1":
                name = input("고객 이름: ")
                email = input("고객 이메일: ")
                c_id = shop.create_customer(DB_FILE, name, email)
                print(f"🎉 고객 등록 완료 (ID: {c_id})")
                
            case "2":
                c_id = int(input("주문할 고객 ID: "))
                o_id = shop.create_order(DB_FILE, c_id)
                print(f"📦 주문서 생성 완료 (주문번호: {o_id})")
                
                # 연속해서 상품 입력 받기
                p_name = input("상품명: ")
                qty = int(input("수량: "))
                price = int(input("가격: "))
                shop.create_order_item(DB_FILE, o_id, p_name, qty, price)
                print("🛒 상품 추가 완료")
                
            case "3":
                c_id = int(input("조회할 고객 ID: "))
                orders = shop.get_customer_orders(DB_FILE)
                
                print(f"\n--- [고객 번호 {c_id}의 영수증] ---")
                for row in orders:
                    print(f"주문번호: {row[1]} | 상품: {row[3]} | 수량: {row[4]} | 가격: {row[5]}원")
                    
            case "4":
                c_id = int(input("수정할 고객 ID: "))
                new_email = input("새로운 이메일: ")
                shop.update_customer_email(DB_FILE, c_id, new_email)
                print("📝 이메일 수정이 완료되었습니다.")
                
            case "5":
                print("👋 프로그램을 종료합니다.")
                break  # while 루프 탈출
                
            case _:
                # 다른 언어의 default: 와 같은 역할을 합니다.
                # 지정된 케이스(1~5) 외의 다른 값이 들어오면 이곳이 실행됩니다.
                print("❌ 잘못된 번호입니다. 1부터 5 사이의 숫자를 입력해 주세요.")