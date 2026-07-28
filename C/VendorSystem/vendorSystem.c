#include <stdio.h>
#include <sqlite3.h>
#include "VendorSystem.h"
#include "vendor_struct.h"

void CreateDB(char* db_name)
{

    sqlite3* db;
    char* errMsg = NULL;

    if(sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        printf("데이터베이스 열기 실패\n");
        return;
    }

    const char* query =
       "CREATE TABLE IF NOT EXISTS person ("
        "Vendor_id INTEGER PRIMARY KEY,"
        "Vendor_Name TEXT NOT NULL,"
        "Staff_Name TEXT NOT NULLL"
        ");";
   
    if(sqlite3_exec(db, query, NULL, NULL, &errMsg) != SQLITE_OK)
    {
        printf("테이블 생성 실패: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    else {
        printf("%s 테이블 생성완료\n",db_name);
    }

    sqlite3_close(db);

    return;

}

void Insert_manager(char* db_name)
{
   Vendor vendor; //협렵사 정보 구조체 인스턴스
   char sql[500];

    printf("\n--- [데이터 입력] ---\n");
    printf("협력사명: ");
    scanf("%99s", vendor.company);
    printf("담당자명: ");
    scanf("%99s", vendor.manager);
    printf("전화번호: ");
    scanf("%99s", vendor.phone);

    sqlite3* db;
    char* errMsg = NULL;

    if(sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        printf("데이터베이스 열기 실패\n");
        return;
    }

    const char* query =
    "INSERT INTO person VALUES"
        "(1,'이모텍','010-1234-5678'),"
        "(2,'이성전자','010-2345-6789'),"
        "(3,'에스게이','010-3456-7890'),"
        "(4,'RC 모터스','010-4567-8901'),"
        "(5,'좋데제과','010-5678-9012');";

        if(sqlite3_exec(db, query, NULL, NULL, &errMsg) != SQLITE_OK)
        {
            printf("데이터 삽입 실패: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
        else
        {
            printf("데이터 삽입 완료\n");
        }

        sqlite3_close(db);
        return;
}