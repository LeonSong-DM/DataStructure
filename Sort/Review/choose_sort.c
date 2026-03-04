/**
 * @Author: leonsong
 * @Date:   2026-03-04 22:51:44
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-04 23:01:05
 * @Function: 选择排序复现
 */
#include <stdio.h>
#include <stdlib.h>


void chooseSort(int *arr, int size) {
    if (!arr || size <= 1) return;

    for (int i = 0; i < size - 1; i++) {
        
        // 寻找每一回合的最小元素
        int min = arr[i];
        int k = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < min) {
                min = arr[j];
                k = j;
            }
        }

        // 交换
        int tmp = arr[k];
        arr[k] = arr[i];
        arr[i] = tmp;
    }
}

int main() {
    int arr[10] = {7, 3, 5, 6, 9, 8, 2, 3, 0, 4};

    chooseSort(arr, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
