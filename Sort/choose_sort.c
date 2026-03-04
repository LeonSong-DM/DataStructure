/**
 * @Author: leonsong
 * @Date:   2026-03-03 21:59:33
 * @Last Modified by:   leonsong
 * @Last Modified time: 2026-03-04 00:31:50
 * @Function: 选择排序
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * @brief: 生成一个 size 长度的无序随机整数的数组
 * 
 * @param size: 生成数组的长度
 * @return: 结果数组
 */

int *getRandomArray(int size) {
    int *arr = (int*) malloc(sizeof(int) * size);
    
    // 初始化 1~20
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }


    // Fisher-Yates 洗牌
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // 交换
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    return arr;
}   


/**
 * @brief: 检查数组元素是否升序排列
 * 
 * @param array: 待检查数组
 * @param length: 待检查数组长度
 * 
 * @return: 1: 升序排列     0: 非升序排列
 */
int checkASC(int* array, int length) {
    if (!array) return 0;

    for (int i = 0; i < length - 1; i++) {
        if (array[i] <= array[i + 1]) continue;

        return 0;
    }
    
    return 1;
}


/**
 * @brief: 选择排序
 * 
 * @param array: 待排序数组指针
 * @param length: 待排序数组长度
 */
void choose_sort(int *array, int length) {
    if (!array || length <= 0) return;
    
    int min = 0;
    int tmp = 0;
    int k = 0;
    for (int i = 0; i < length - 1; i++) {
        min = array[i];
        k = i;
        for (int j = i + 1; j < length; j++) {
            if (array[j] < min) {
                min = array[j];
                k = j;
            }
        }

        // 与array[i]交换
        tmp = array[i];
        array[i] = min;
        array[k] = tmp;
    }        
}


// INFO: gcc choose_sort.c utils.c -o app && ./app
int main() {
    // 设置随机种子
    srand((unsigned int)time(NULL));

    // TEST: 20轮测试

    int size = 20;
    int *arr;
    for (int i = 0; i < 20; i++) {
        arr = getRandomArray(size);
        // 打印原始数组
        printf("| Round: %-3d | Original: %-4s | ", i + 1, "");
            for (int v = 0; v < size; v++) {
                printf("%d ", arr[v]);
            }
            printf("\n");

        choose_sort(arr, size);

        if (checkASC(arr, size)) {
            printf("| Round: %-3d | Result: %-6s | ", i + 1, "PASS");
            for (int m = 0; m < size; m++) {
                printf("%d ", arr[m]);
            }
            printf("\n------------------------------------------------------------------------------------\n");
        } else {
            printf("| Round: %-3d | Result: %-6s | ", i + 1, "FAIL");
            for (int m = 0; m < size; m++) {
                printf("%d ", arr[m]);
            }
            printf("\n");
        }
    }
    
    return 0;
}
