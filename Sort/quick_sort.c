/**
 * @Author: leonsong
 * @Date:   2026-03-04 20:20:02
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-05 14:41:12
 * @Function: 快速排序
 */
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief: 根据基准元素划分数组
 * 
 * @param arr: 待划分数组
 * @param low: 起始索引
 * @param high: 终止索引
 * 
 * @return: 划分后基准元素的索引 
 */
int partition(int *arr, int low, int high) {
    if (!arr || low >= high) return -1;
    
    int pivot = arr[low];   // 基准元素
    printf("%s: %d\n", "基准元素", pivot);
    int i = low + 1;    // 等价于i = low, 因为i指针首次进入循环一定满足arr[i] == pivot
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
// INFO: 划分的实际意义
// 左指针i会不断向右遍历元素直到找到arr[i] > pivot
// 右指针j不断向左遍历元素直到找到arr[j] < pivot
// 也就是说, i右移是在不断扩大 <= pivot 的区域, j左移是在不断扩大 >= pivot的区域
// 直到i与j相交, 该位置就是基准元素的插入位置
// 此时就满足[element <= pivot] pivot [element >= pivot]

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
