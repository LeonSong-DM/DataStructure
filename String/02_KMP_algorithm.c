/*
 * @Author: LeonSong 
 * @Date: 2026-02-26 08:50:04 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-03-02 18:02:16
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 计算PMT数组
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


int KMPMatch(char *main, char *pattern) {
    if (!main || !pattern) return -1;

    // 获取长度
    int m_len = strlen(main);
    int p_len = strlen(pattern);

    // 模式串长度 > 主串
    if (m_len < p_len) return -1;
    // 模式串为空, 返回0
    if (p_len == 0) return 0;

    int i = 0;
    int j = 0;

    // 获取pmt数组
    int *pmt = getPMT(pattern);
    if (!pmt) return -1;

    while (i < m_len) {
        if (main[i] == pattern[j]) {
            i++;
            j++;
            
            if (j == p_len) {
                free(pmt);
                return i - j;
            }
        } else {

            if (j > 0) {
                j = pmt[j - 1];
            } else {
                j = 0;
                i++;
            }
        }
    }
    
    free(pmt);
    return j == p_len ? i - j : -1;
}


int main() {
    char *main = "acaacbaac";
    char *pattern = "baac";
    int index = KMPMatch(main, pattern);
    printf("%d\n", index);
    return 0;
}