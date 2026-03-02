/*
 * @Author: LeonSong 
 * @Date: 2026-03-02 13:43:51 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-03-02 17:38:23
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* getPMT(char *s) {
    if (!s) return NULL;

    int len = strlen(s);
    // 空串
    if (len == 0) return NULL;

    // 声明结果数组
    int *pmt = (int*) malloc(sizeof(int) * len);
    if (!pmt) return NULL;
    pmt[0] = 0;

    // 定义指针
    int i = 1;
    int j = 0;

    while (i < len) {
        // 匹配成功
        if (s[j] == s[i]) {
            j++;
            pmt[i] = j;
            i++;
        } else {    // 匹配失败
            if (j == 0) {
                pmt[i] = j;
                i++;
            } else {    // 匹配失败 && j > 0
                j = pmt[j - 1];
            }
        }
    }

    return pmt;
}


int main() {
    char *str =  "abaabf";  // 0 0 1 1 2 0
    int *res = (int*) malloc(sizeof(int) * strlen(str));
    res = getPMT(str);
    
    for (int i = 0; i < strlen(str); i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}