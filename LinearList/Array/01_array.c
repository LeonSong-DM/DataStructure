/* 二维数组 */

#include<stdio.h>


int main() {
    int a = 10;
    printf("%p\n", &a);

    int arr[3][4] = {0};
    printf("%p\n", &arr[2][0]);
    printf("%p\n", &arr[2][1]);
    printf("%p\n", &arr[2][2]);
    return 0;
}