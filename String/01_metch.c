/*
 * @Author: LeonSong 
 * @Date: 2026-02-03 17:37:07 
 * @Last Modified by: LeonSong
 * @Last Modified time: 2026-02-03 18:49:04
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int match(char *S, char *T) {
    int i, j = 0;
    int s_length = strlen(S);
    int t_length = strlen(T);
    while (i < s_length && j < t_length) {
        if (S[i] == T[j]) {
            i++;
            j++;
        } else {  
            i = i - j + 1;
            j = 0;
        }
    }

    if (j > t_length - 1) {
        return i - j;
    }
    return -1;
}

int main() {
    char S[100] = "Hello World.01010101010101010101010101010101010100";
    char T[4] = "100";
    int index;
    index = match(S, T);
    printf("%d\n", index);

    
}