#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main() {
    freopen("lcs_input.txt", "r", stdin);
    char src[1001]; char dst[1001];
    scanf("%s %s", src, dst);

    int s_len = strlen(src);
    int d_len = strlen(dst);

    // 이차 동적 배열
    int** arr = (int**)malloc(sizeof(int*) * (d_len + 1));
    for (int i = 0; i <= d_len; ++i)
        arr[i] = (int*)malloc(sizeof(int) * (s_len + 1));

    for (int i = 1; i <= d_len; ++i) {
        for (int j = 1; j <= s_len; ++j) {
            if (src[j - 1] == dst[i - 1])
                arr[i][j] = arr[i - 1][j - 1] + 1;
            else {
                if (arr[i - 1][j] < arr[i][j - 1])
                    arr[i][j] = arr[i][j - 1];
                else
                    arr[i][j] = arr[i - 1][j];
            }
        }
    }

    printf("%d\n", arr[d_len][s_len]);

    // 배열 지우기
    for (int i = 0; i <= d_len; ++i)
        free(arr[i]);
    free(arr);
}