#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

bool check(int arr[], int length) {
    int old = arr[0];
    for (int i = 1; i < length; ++i) {
        if (arr[i] >= old) { old = arr[i]; } else return false;
    }
    return true;
}

int get_sep(int arr[], int s, int e) {
    int p = s - 1;
    for (int i = s; i < e; ++i) {
        if (arr[i] < arr[e]) {
            p += 1;
            int temp = arr[i]; arr[i] = arr[p]; arr[p] = temp;
        }
    }

    p += 1;
    int temp = arr[p]; arr[p] = arr[e]; arr[e] = temp;

    return p;
}

void process(int arr[], int s, int e) {
    if (s >= e) return;

    int sep = get_sep(arr, s, e);
    process(arr, s, sep - 1);
    process(arr, sep + 1, e);
}

int main() {
    srand(time(NULL));
    int arr[1000];
    for (int i = 0; i < 1000; ++i) { arr[i] = rand() % 1000 - 500; }
    int length = sizeof(arr) / sizeof(arr[0]);

    process(arr, 0, length - 1);
    for (int i = 0; i < length; ++i) {
        if (i % 20 == 0) printf("\n");
        printf("%4d ", arr[i]);
    }
    puts("");

    if (check(arr, length)) puts("OK!"); else puts("FAILED");
}