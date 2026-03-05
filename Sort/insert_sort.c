/**
 * @Author: leonsong
 * @Date:   2026-03-04 16:09:10
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-05 12:02:39
 * @Function: 插入排序
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 插入排序
 * 
 * @param arr: 待排序数组
 * @param size: 待排序数组长度
*/
void insertSort(int *arr, int size) {
    // INFO: 共循环size - 1轮, 未排序区间是[i, size - 1]
    for (int i = 1; i < size; i++) {
        int base = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > base) {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j + 1] = base;
    }
}

void insertSortV2(int *arr, int size) {
    if (!arr || size <= 1) return;
    
    for (int i = 1; i < size; i++) {
        int base = arr[i];
        int j = i - 1;
        
        for (; j >= 0; j--) {
            if (arr[j] > base) {
                arr[j+1] = arr[j];  // 右移
            } else {
                break;
            }
        }

        arr[j + 1] = base;
        
    }
}

int main() {
    int size = 5;
    int *arr = (int*) malloc(sizeof(int) * size);
    arr[0] = 5;
    arr[1] = 4;
    arr[2] = 3;
    arr[3] = 2;
    arr[4] = 1;

    insertSortV2(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
