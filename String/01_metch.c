/*
 * @Author: LeonSong 
 * @Date: 2026-02-03 17:37:07 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-02-05 21:43:11
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int match(char *S, char *T) {
    if (!S || !T) return -1;

    int s_len = strlen(S);
    int t_len = strlen(T);

    //空匹配
    if (t_len == 0) return 0;

    int i = 0, j = 0;
    while (S[i] && T[j]) {
        if (S[i] == T[j]) {
            i++;
            j++;
        } else {
            // 此时,子串中[0, j-1]一定是完全匹配的, 也就是说在主串[x, i-1]是完全匹配的
            // 已知共j个元素完全匹配, 可以的主串开始的位置x = i - j,后移一位便是i-j+1
            i = i - j + 1;
            j = 0;
        }
    }
    // 匹配成功标志
    return j == t_len ? i - j : -1;
}

int main() {
    char *S = "Hello World";
    char *T = "llo ";

    int index = match(S, T);
    if (index == -1) {
        printf("%s\n", "Match Wrong.");
    } else {
        printf("%s%d\n", "The index is: ", index);
    }

}