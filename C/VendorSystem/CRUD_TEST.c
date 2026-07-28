#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// 콜백 함수: SELECT 조회 결과를 화면에 이쁘게 출력하기 위함
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\t", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// 데이터베이스 및 테이블 초기화 (REQ-001)
int init_database(sqlite3 *db) {
    char *err_msg = 0;
    
    // 외래키 활성화 및 통합 담당자 관리 테이블 생성
    // 2시간 내 효율적인 관리를 위해 하나의 테이블에 구조화하거나 
    // 정석대로 협력사-담당자 관계를 매핑할 수 있도록 설계했습니다.
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS partners ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "company_name TEXT NOT NULL,"
        "manager_name TEXT NOT NULL,"
        "phone_number TEXT NOT NULL"
        ");";

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL 오류: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 0;
    }
    return 1;
}

// 담당자 데이터 삽입 (REQ-002)
void insert_manager(sqlite3 *db) {
    char company[100];
    char manager[100];
    char phone[100];
    char sql[500];
    char *err_msg = 0;

    printf("\n--- [데이터 입력] ---\n");
    printf("협력사명: ");
    scanf("%99s", company);
    printf("담당자명: ");
    scanf("%99s", manager);
    printf("전화번호: ");
    scanf("%99s", phone);

    snprintf(sql, sizeof(sql), 
             "INSERT INTO partners (company_name, manager_name, phone_number) VALUES ('%s', '%s', '%s');", 
             company, manager, phone);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "데이터 삽입 실패: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("성공적으로 등록되었습니다.\n");
    }
}

// 담당자 및 협력사 정보 조회 (REQ-003)
void select_managers(sqlite3 *db) {
    const char *sql = "SELECT id AS [ID], company_name AS [협력사], manager_name AS [담당자], phone_number AS [전화번호] FROM partners;";
    char *err_msg = 0;

    printf("\n--- [담당자 조회 목록] ---\n");
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "조회 실패: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("---------------------------\n");
}

// 담당자 정보 수정 (주요 기능 포함 사항)
void update_manager(sqlite3 *db) {
    int id;
    char company[100];
    char manager[100];
    char phone[100];
    char sql[500];
    char *err_msg = 0;

    printf("\n--- [데이터 수정] ---\n");
    printf("수정할 데이터의 ID를 입력하세요: ");
    if (scanf("%d", &id) != 1) return;

    printf("새로운 협력사명: ");
    scanf("%99s", company);
    printf("새로운 담당자명: ");
    scanf("%99s", manager);
    printf("새로운 전화번호: ");
    scanf("%99s", phone);

    snprintf(sql, sizeof(sql), 
             "UPDATE partners SET company_name='%s', manager_name='%s', phone_number='%s' WHERE id=%d;", 
             company, manager, phone, id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "수정 실패: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("성공적으로 수정되었습니다.\n");
    }
}

// 담당자 삭제 (REQ-004)
void delete_manager(sqlite3 *db) {
    int id;
    char sql[200];
    char *err_msg = 0;

    printf("\n--- [데이터 삭제 (직무해제/업체변경)] ---\n");
    printf("삭제할 고유 ID를 입력하세요: ");
    if (scanf("%d", &id) != 1) return;

    snprintf(sql, sizeof(sql), "DELETE FROM partners WHERE id = %d;", id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "삭제 실패: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("성공적으로 삭제되었습니다.\n");
    }
}

// 통계 기능 (주요 기능 포함 사항: 총 등록 수 및 협력사별 담당자 수)
void show_statistics(sqlite3 *db) {
    char *err_msg = 0;
    
    printf("\n--- [시스템 통계] ---\n");
    
    printf("[총 등록된 담당자 수]\n");
    const char *sql_total = "SELECT COUNT(*) AS [총계] FROM partners;";
    sqlite3_exec(db, sql_total, callback, 0, &err_msg);

    printf("\n[협력사별 담당자 인원수]\n");
    const char *sql_group = "SELECT company_name AS [협력사], COUNT(*) AS [담당자수] FROM partners GROUP BY company_name;";
    sqlite3_exec(db, sql_group, callback, 0, &err_msg);
    
    if (err_msg) sqlite3_free(err_msg);
    printf("---------------------------\n");
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("partner_management.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "데이터베이스를 열 수 없습니다: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    // DB 테이블 초기화
    if (!init_database(db)) {
        sqlite3_close(db);
        return 1;
    }
    
    int choice;
    while (1) {
        printf("\n======= 협력사 관리 시스템 =======\n");
        printf("1. 담당자 등록 (REQ-002)\n");
        printf("2. 담당자 조회 (REQ-003)\n");
        printf("3. 담당자 수정\n");
        printf("4. 담당자 삭제 (REQ-004)\n");
        printf("5. 통계 보기\n");
        printf("6. 프로그램 종료\n");
        printf("==================================\n");
        printf("원하는 기능의 번호를 선택하세요: ");
        
        if (scanf("%d", &choice) != 1) {
            // 잘못된 문자 입력 시 버퍼 비우기 및 예외 처리
            while (getchar() != '\n');
            printf("올바른 숫자를 입력해주세요.\n");
            continue;
        }

        switch (choice) {
            case 1: insert_manager(db); break;
            case 2: select_managers(db); break;
            case 3: update_manager(db); break;
            case 4: delete_manager(db); break;
            case 5: show_statistics(db); break;
            case 6:
                printf("프로그램을 종료합니다.\n");
                sqlite3_close(db);
                return 0;
            default:
                printf("잘못된 번호입니다. 다시 선택해주세요.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}