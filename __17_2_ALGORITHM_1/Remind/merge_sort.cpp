#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void merge_sort(int arr[], int s, int e) {
    if (s >= e) return;
    // 분할
    int sep = (s + e) / 2;
    merge_sort(arr, s, sep); merge_sort(arr, sep + 1, e);

    // 정복
    int l_len = sep - s + 1; // s ~ sep 까지
    int* l_arr = (int*)malloc(sizeof(int) * l_len);
    for (int i = 0; i < l_len; ++i) { l_arr[i] = arr[s + i]; }

    int r_len = e - sep; // sep + 1 ~ end 까지
    int* r_arr = (int*)malloc(sizeof(int) * r_len);
    for (int i = 0; i < r_len; ++i) { r_arr[i] = arr[sep + 1 + i]; }

    // 정복 2
    int l = 0, r = 0, i = s;// s ~ e 까지 차곡차곡
    while (l < l_len && r < r_len) {
        if (l_arr[l] > r_arr[r]) {
            arr[i] = r_arr[r];
            ++r; ++i;
        }
        else {
            arr[i] = l_arr[l];
            ++l; ++i;
        }
    }

    while (l < l_len) { arr[i] = l_arr[l]; ++l; ++i; }
    while (r < r_len) { arr[i] = r_arr[r]; ++r; ++i; }
    free(l_arr); free(r_arr);
}

int main() {
    srand(time(NULL));
    int arr[1000];
    for (int i = 0; i < 1000; ++i) { arr[i] = rand() % 1000 - 500; }
    int length = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, 0, length - 1);
    for (int i = 0; i < length; ++i) {
        if (i % 20 == 0) printf("\n");
        printf("%4d ", arr[i]);
    }
    puts("");
}