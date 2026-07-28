#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "CRUD.h"

int main()
{
	int choice;

	while (1)
	{
		printf("\n--- 자재 협력사 담당자 관리 시스템 ---\n");
		printf("1. 협력사/담당자 등록 (C)\n");
		printf("2. 전체 담당자 조회 (R)\n");
		printf("3. 담당자 정보 수정 (U)\n");
		printf("4. 담당자 삭제 (D)\n");
		printf("5. 프로그램 종료\n");
		printf("선택: ");
		if (scanf("%d", &choice) != 1) {
		
			printf("숫자만 입력 가능합니다.\n");

			while (getchar() != '\n');

			continue; 
		};

		switch (choice)
		{
		case 1:
			create_vendor();
			break;
		case 2:
			read_vendor();
			break;
		case 3:
			update_vendor();
			break;
		case 4: 
			delete_vendor();
			break;
		case 5:
			printf("데이터를 저장하고 프로그램을 종료합니다.\n");
			return 0;
		default:
			printf("잘못된 선택입니다. 다시 입력해주세요.\n");

		}
		

	}
	return 0;
}