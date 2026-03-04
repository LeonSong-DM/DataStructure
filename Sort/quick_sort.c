/**
 * @Author: leonsong
 * @Date:   2026-03-04 20:20:02
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-04 22:43:30
 * @Function: 快速排序
 */
#include <stdio.h>
#include <stdlib.h>


int partition(int *arr, int low, int high) {
    if (!arr || low >= high) return -1;
    
    int pivot = arr[low];   // 基准元素
    printf("%s: %d\n", "基准元素", pivot);
    int i = low;
    int j = high;

    
    while (i < j) {
        while (i < j && arr[j] >= pivot) {
            j--;   
        }
        while (i < j && arr[i] <= pivot) {
            i++;
        }
        
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }

    // 移动pivot
    arr[low] = arr[j];
    arr[j] = pivot;
    
    return i;
}

void quickSort(int *arr, int low, int high) {
    if (low >= high) return;
    
    int pivot = partition(arr, low, high);
    quickSort(arr, low, pivot - 1);
    quickSort(arr, pivot + 1, high);
}


int main() {
    int arr[10] = {200, 100, 5, 6, 9, 8, 2, 3, 0, 4};
    quickSort(arr, 0, 9);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
