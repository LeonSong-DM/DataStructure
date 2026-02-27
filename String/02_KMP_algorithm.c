/*
 * @Author: LeonSong 
 * @Date: 2026-02-26 08:50:04 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-02-26 19:03:51
 */

#include <stdio.h>
#include <string.h>


// 对字符串进行切片
char* slice(char *s, int start, int end) {
    if (!s || start > end) return NULL;
    
    char res[end - start + 1];
    for (int i = start; i <= end; i++) {
        res[i-start] = s[i];
    }

    return res;
}

// 计算KMP数组
int* getKMP(char *s) {
    if (!s) return NULL;
    
    int s_len = strlen(s);
    int kmp[s_len];
    
}

int KMPMatch(char *main, char *pattern) {
    // 校验参数合法性
    if (!main || !pattern) return -1;

    // 计算长度
    int main_len = strlen(main);
    int pattern_len = strlen(pattern);

    if (main_len < pattern_len) {
        return -1;
    } else if (pattern_len == 0) {      // 处理模式串为0的情况
        return 0;
    }

    // 声明指针
    int i = 0;
    int j = 0;

    // 获取KMP数组
    int *kmp = getKMP(pattern);

    //TODO 考虑循环的条件
    while (main[i]) {
        if (main[i] == pattern[j]) {
            i++;
            j++;

            // 匹配成功
            if (j == pattern_len) return i - j;

        } else {

            if (j == 0) {
                i++;                // 在 j = 0 处失配时
            } else {
                j = kmp[j - 1];     // NOTICE 这里有可能会溢出
            }

        }
    }

    return -1;

}


int main() {
    char *main = "acaacbaac";
    char *pattern = "aac";
    // int index = KMPMatch(main, pattern);
    // printf("%d\n", index);
    return 0;
}