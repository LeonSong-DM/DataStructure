/**
 * @Author: leonsong
 * @Date:   2026-03-04 14:41:54
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-04 15:53:26
 * @Function: 冒泡排序实现
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief: 冒泡排序
 * 
 * @param arr: 待排序数组
 * @param size: 待排序数组的长度
 */

void bubbleSort(int *arr, int size) {
    if (!arr || size <= 1) return;

    int flag = 0;   // 交换操作标志
    int tmp = 0;    // 临时交换变量
    
    // INFO: 外层循环代表未排序区间, 只需要对n-1个元素进行排序
    for (int i = size - 1; i > 0; i--) {    
        flag = 0;   
        
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1]) {
                // 交换
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                flag = 1;
            }
        }

        // LOG
        printf("|%-4s %d| ", "Round", size - i);
        for (int k = 0; k < size; k++) {
            printf("%d ", arr[k]);
        }
        printf("|\n");

        if (!flag) return;  // 某轮没有发生交换
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

    bubbleSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
