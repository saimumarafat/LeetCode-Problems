#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0)
        return "";

    int i, j;

    for (i = 0; strs[0][i] != '\0'; i++) {
        char c = strs[0][i];

        for (j = 1; j < strsSize; j++) {
            if (strs[j][i] != c) {
                strs[0][i] = '\0';
                return strs[0];
            }
        }
    }

    return strs[0];
}