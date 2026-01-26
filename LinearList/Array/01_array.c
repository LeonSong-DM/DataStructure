/* 二维数组 */

#include<stdio.h>


int main() {
    int arr[3][4] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}