#include <stdio.h>
#include <string.h> // strlen 함수를 쓰기 위해 포함

int main()
{
    char name[9];
    char* copy1;
    char* copy2;
    int length = sizeof(name) / sizeof(name[0]);

        fgets(name, length, stdin);
    


       copy1 = name;                         // copy는 시작 글자 지점
    copy2 = name + strlen(name) - 1;    // name2는 실제 문자열의 '마지막 글자' 지점 (\0 직전)

       while (copy1 < copy2)
    {
        char temp = *copy1;
        *copy1 = *copy2;
        *copy2 = temp;

        copy1++;  // 오른쪽으로 이동
        copy2--; // 왼쪽으로 이동
    }


    printf("%s\n", name);

    return 0;
}
