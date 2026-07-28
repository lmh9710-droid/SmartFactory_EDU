#include <stdio.h>
#include <sqlite3.h>
#include "sqlite_test.h"
#include "print_menu.h"
#define DBNAME ("vendor.db")

int main()
{
    sqlite3* db;
    int choice;
    
    CreateDB(DBNAME, db);
    
    while(1)
    {// 테이블 생성
      print_menu(); //메뉴 출력 
      scanf("%d", &choice);

        switch(choice)
       {
          case 1:
            InsertDB(DBNAME, db) ;
            break;

          case 2:
            SelectDB(DBNAME, db);
            break;

          case 3:
            UpdateDB(DBNAME, db);
            break;

          case 4:
            DeleteDB(DBNAME, db);
            break;

          case 6:
            printf("프로그램을 종료합니다.\n");
            return 0;
            

        } 

   
   } 

   return 0;
}