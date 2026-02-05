/*
 * @Author: LeonSong 
 * @Date: 2026-02-03 22:08:01 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-02-03 22:25:01
 */

#include <stdio.h>

/**
 * @brief 二分查找 - 基础实现
 * @param arr       查询数组
 * @param len       查询数组的长度
 * @param target    目标值
 */
int binarySearch(int *arr, int len, int target) {
    if (!arr) return -1;
    int i = 0;
    int j = len - 1;
    while (i <= j) {
        int m = i + (j - i) / 2;
        if (target < arr[m]) {
            j = m - 1;
        } else if (target > arr[m]) {
            i = m + 1;
        } else {
            return m;
        }
        
    }
    return -1;
}

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i ++) {
        int index = binarySearch(arr, 9, i);
        printf("The Target index is : %d\n", index);
    }
    return 0;
}