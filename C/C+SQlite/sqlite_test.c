#include <stdio.h>
#include <sqlite3.h>
#include "sqlite_test.h"
#include "vendor_struct.h"

void CreateDB(char* db_name, sqlite3* db)
{

    
    char* errMsg = NULL;

    if(sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        printf("데이터베이스 열기 실패\n");
        return;
    }

    const char* query =
       "CREATE TABLE IF NOT EXISTS person ("
        "id INTEGER PRIMARY KEY,"
        "vendor TEXT NOT NULL,"
        "staff_name TEXT NOT NULL,"
        "phone_number TEXT NOT NULL"
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

void InsertDB(char* db_name, sqlite3* db)
{
    
    char* errMsg = NULL;
    char query[500];

    Vendor vendor;

    printf("협력사 ID: ");
    scanf("%99d", &vendor.id );
    printf("협력사명: ");
    scanf("%99s", vendor.company);
    printf("담당자명: ");
    scanf("%99s", vendor.manager);
    printf("전화번호: ");
    scanf("%99s", vendor.phone);



    printf("\n---[데이터 입력]---\n");



    if(sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        printf("데이터베이스 열기 실패\n");
        return;
    }

    snprintf(query, sizeof(query), "insert into person values('%d', '%s', '%s', '%s');"
    ,vendor.id , vendor.company, vendor.manager, vendor.phone);

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

void SelectDB(char* db_name, sqlite3* db)
{
    sqlite3_stmt* stmt;

    if(sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        printf("데이터베이스 열기 실패\n");
        return;
    }

    const char* query = "select id, vendor, staff_name, phone_number from person;";

    if(sqlite3_prepare_v2(db, query, -1, &stmt, NULL)!= SQLITE_OK)
    {
        printf("조회 준비 실패\n");
        sqlite3_close(db);
    }

    printf("ID\tVENDOR\tNAME\tPHONE\n");

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* VENDOR = sqlite3_column_text(stmt, 1);
        const unsigned char* NAME = sqlite3_column_text(stmt, 2);
        const unsigned char* PHONE = sqlite3_column_text(stmt, 3);

        printf("%d\t%s\t%s\t%s\n", id, VENDOR, NAME, PHONE);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return;

}

void UpdateDB(char* db_name, sqlite3* db)
{
    char *errMsg = NULL;
    char query[500];
   
    Vendor vendor;

    if(sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        printf("데이터베이스 열기 실패\n");
        return;
    }
    
    printf("수정할 ID를 입력하새요: ");
    scanf("%d", &vendor.id);

    printf("새로운 협렵사명: ");
    scanf("%99s", vendor.company);

    printf("새로운 담당자명: ");
    scanf("%99s", vendor.manager);

    printf("새로운 전화번호: ");
    scanf("%99s", vendor.phone);

    snprintf(query, sizeof(query), "UPDATE person SET vendor ='%s', staff_name='%s', phone_number='%s' WHERE id=%d;", 
             vendor.company, vendor.manager, vendor.phone, vendor.id);

        if(sqlite3_exec(db, query, NULL, NULL, &errMsg) != SQLITE_OK)
        {
            printf("데이터 업데이트 실패: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
        else
        {
            printf("데이터 삽입 완료\n");
        }

        sqlite3_close(db);
        return;
}

void DeleteDB(char* db_name, sqlite3* db)
{
    char *errMsg = NULL;
    char query[500];
    int delete_id;

    printf("삭제할 ID를 입력하세요: ");
    scanf("%d", &delete_id);

    if(sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        printf("데이터베이스 열기 실패\n");
        return;
    }

    snprintf(query, sizeof(query), "delete from person where id = %d;"
             , delete_id);

    if(sqlite3_exec(db, query, NULL, NULL, &errMsg) != SQLITE_OK)
    {
       printf("데이터 삭제 실패: %s\n", errMsg);
       sqlite3_free(errMsg);
    }
    else
    {
       printf("데이터 삭제 완료\n");
    }

    sqlite3_close(db);
    return;

}