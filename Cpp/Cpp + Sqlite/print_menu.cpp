#include "print_menu.h"
#include <sqlite3.h>

using namespace std;


Menu::Menu(const char* db_name, sqlite3* db)
:DataBase(db_name, db)
{
}

void Menu::Print_Menu() const
{
    cout <<"--협렵사 관리 시스템--"<<endl
         <<"1. 협력사 등록" << endl
         <<"2. 등록된 협렵사 조회" << endl
         <<"3. 협렵사 업데이트"<< endl
         <<"4. 협렵사 삭제" << endl 
         <<"5. 시프템을 종료 합니다."<< endl;

}

void Menu::Switch_Case()
{
 Menu::Create_DB();
 
 while(1) {
   int choice;
   cout<<"번호 선택:";
   cin >> choice;


   switch(choice)
   {
     case 1: 
       Menu::Insert_DB(); //Table 정보 삽입
       break;
     case 2: 
       Menu::Select_DB(); //Table 데이터 조회
       break;
     case 3: 
       Menu::Update_DB(); //Table 데이터 업데이트 
       break;
     case 4: 
       Menu::Delete_DB(); //Table 데이터 삭제 
       break; 
     case 5: 
       return;
       break;
     default:
      cout<<"잘못 입력 되었습니다."<< endl; 
   }
 }
}

Menu::~Menu()
{
  cout<< "child 파괴자 호출되었습니다." << endl;
}

