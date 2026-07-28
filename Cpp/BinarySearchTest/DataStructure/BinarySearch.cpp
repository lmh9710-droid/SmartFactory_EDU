#include <stdio.h>
#include <string.h>
#include <iostream>
#include <chrono> 
#include <iomanip>


int BinarySearch(int* a, const int x, const int n)
{
    int left = 0, right = n-1;

    while(left <= right)
    {  
        int middle = right - left/2;
        if(x<a[middle])
        {
            right = middle -1;
        }

        else if(x>a[middle])
        {
            left = middle+1;
        }

        else {
            return middle;
        }

    
    }
    return -1; // 발견되지 않음
}

int SearchArray (int *a, int x, int n)
{
   for(int i = 0; i < n ; i++)
   {
      if(x == *a++)
      {
             
        return i;

      }

   }

   return -1; // 발견되지 않음

}

int main(void)
{
    int arr[] = {1, 2, 4, 5, 6, 7, 9, 10, 40, 50};
    int alen = sizeof(arr)/sizeof(int);

    auto start1 = std::chrono::high_resolution_clock::now();
    int result1 = SearchArray(arr, 9, alen);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    int result2 = BinarySearch(arr, 9, alen);
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration1 = end1 - start1;
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;


    // printf("%d", alen);
    printf("SearchArray: %d\t", result1);
    std::cout << "함수 실행 시간" 
              << std::fixed << std::setprecision(6)
              << duration1.count() << "ms "<< std::endl;
    printf("BinarySearch: %d\t", result2);
    std::cout << "함수 실행 시간" 
              << std::fixed << std::setprecision(6)
              << duration2.count() << "ms" << std::endl;

    return 0;
}