/*
 * @Author: LeonSong 
 * @Date: 2026-02-27 23:18:43 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-02-27 23:33:36
 */

#include <stdio.h>
#include <stdlib.h>

int* twoSum(int *nums, int num_size, int target, int* return_size) {
    // 检验合法性
    if (!nums || !return_size || num_size < 2) return NULL;

    *return_size = 2;
    // 定义结果数组
    int *arr = (int*) malloc(sizeof(int) * (*return_size));

    for (int i = 0; i < num_size; i++) {
        for (int j = i + 1; j < num_size; j++) {
            if (nums[i] + nums[j] == target && i != j) {
                arr[0] = i;
                arr[1] = j;
                return arr;
            }
        }
    }
    free(arr);
    return NULL;
}



int main() {
    
}