#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "CRUD.h"
#include "vendor_t.h"
#define FILENAME ("vendor.txt")



void create_vendor()
{
	FILE* fp;
	Vendor vendor = { 0,"","","","" };


	printf("담당자 ID: ");
	if (scanf("%d", &vendor.id) != 1)
	{
		printf("숫자만 입력하세요.\n");
		while (getchar() != '\n');
		return;
	}


	printf("협력사: ");
	if (scanf("%s", vendor.vendor) != 1)
	{
		printf("입력 오류");
	}

	printf("담당자 이름: ");
	if (scanf("%s", vendor.name) != 1)
	{
		printf("입력 오류");
	}

	printf("담당자 직급: ");
	if (scanf("%s", vendor.position) != 1)
	{
		printf("입력 오류");
	}

	printf("담당자 HP: ");
	if (scanf("%s", vendor.phone) != 1)
	{
		printf("입력 오류");
	}

	fp = fopen(FILENAME, "a");

	if (fp == NULL)
	{
		printf("파일 열기 실패\n");
		return;
	}

	fprintf(fp, "%d,%s,%s,%s,%s",
		vendor.id,
		vendor.vendor,
		vendor.name,
		vendor.position,
		vendor.phone);

	fclose(fp);

	printf("제품 추가 완료\n");

}

void read_vendor()
{
	FILE* fp;
	Vendor vendor = { 0,"","","","" };;

	fp = fopen(FILENAME, "r");

	if (fp == NULL)
	{
		printf("파일 열기 실패\n");
		return;
	}

	printf("\n=======================================\n");
	printf(" 사번/ID | 협력사 | 이름 | 직급 | 연락처 \n");
	printf("=========================================\n");

	while (fscanf(fp, "%d,%79[^,],%29[^,],%19[^,],%19[^,]",
		   &vendor.id,
		    vendor.vendor,
		    vendor.name,
		    vendor.position,
		    vendor.phone) == 5)
	{
		printf("%5d\t%5s\t%5s\t%5s\t%5s",
			vendor.id,
			vendor.vendor,
			vendor.name,
			vendor.position,
			vendor.phone);
	}

	fclose(fp);
	
}

void update_vendor()
{
	FILE* src;
	FILE* temp;

	Vendor vendor = { 0,"","","","" };

	int targetID;
	char newVendor[80];
	int found = 0;

	printf("수정할 번호 입력: ");
	scanf("%d", &targetID);

	printf("새 협력사 입력: ");
	scanf("%s", newVendor);



	src = fopen(FILENAME, "r");
	temp = fopen("temp.txt", "w");

	if (src == NULL || temp == NULL)
	{
		printf("파일 열기 실패\n");
		return;
	}

	while (fscanf(src, "%d,%79[^,],%29[^,],%19[^,],%19[^,]",
		&vendor.id,
		vendor.vendor,
		vendor.name,
		vendor.position,
		vendor.phone) == 5)
	{
		if (vendor.id == targetID)
		{
			memcpy(vendor.vendor, newVendor, sizeof(vendor.vendor));
			found = 1;
		}

		fprintf(temp, "%d,%s,%s,%s,%s",
			vendor.id,
			vendor.vendor,
			vendor.name,
			vendor.position,
			vendor.phone);


	}

	fclose(src);
	fclose(temp);

	remove(FILENAME);
	rename("temp.txt", FILENAME);

	if (found)
	{
		printf("협력사 수정 완료\n");
	}

	else {
		printf("해당 번호가 없습니다.\n");
	}

}

void delete_vendor()
{
	FILE* src;
	FILE* temp;

	Vendor vendor = { 0,"","","","" };

	int targetID;
	int found;

	printf("삭제할 번호 입력: ");
	scanf("%d", &targetID);

	src = fopen(FILENAME, "r");
	temp = fopen("temp.txt", "w");

	if (src == NULL || temp == NULL)
	{
		printf("파일 열기 실패\n");
		return;
	}

	while (fscanf(src, "%d,%79[^,],%29[^,],%19[^,],%19[^,]",
		&vendor.id,
		vendor.vendor,
		vendor.name,
		vendor.position,
		vendor.phone) == 5)
	{
		if (vendor.id == targetID)
		{
			found = 1;
			continue;
		}

		fprintf(temp, "%d,%s,%s,%s,%s",
			vendor.id,
			vendor.vendor,
			vendor.name,
			vendor.position,
			vendor.phone);


	}

	fclose(src);
	fclose(temp);

	remove(FILENAME);
	rename("temp.txt", FILENAME);

	if (found)
	{
		printf("삭제 완료\n");
	}

	else {
		printf("해당 번호가 없습니다.\n");
	}
   
}