#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define SIZE 10000

void heapify(int arr[], int i, int end) {
    int old = i;
    int l = 2 * i + 1;
    int r = l + 1;

    if (arr[old] < arr[l] && l <= end)
        old = l;
    if (arr[old] < arr[r] && r <= end)
        old = r;
    
    if (i != old) {
        int temp = arr[i]; arr[i] = arr[old]; arr[old] = temp;
        heapify(arr, old, end);
    }
}

void process(int arr[], int size) {
    for (int i = size / 2; i >= 0; --i)
        heapify(arr, i, size - 1);

    int i = size - 1;
    while (i > 0) {
        int temp = arr[0]; arr[0] = arr[i]; arr[i] = temp;
        i--;
        heapify(arr, 0, i);
    }
}

bool check(int arr[], int length) {
    int old = arr[0];
    for (int i = 1; i < length; ++i) {
        if (arr[i] >= old) { old = arr[i]; } else return false;
    }

    return true;
}

int main() {
    srand(time(NULL));
    int* arr = (int*) malloc(sizeof(int) * SIZE);
    for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 1000 - 500; }

    process(arr, SIZE);
    for (int i = 0; i < SIZE; ++i) {
        if (i % 20 == 0) std::cout << '\n';
        printf("%4d ", arr[i]);
    }
    puts("");

    if (check(arr, SIZE)) puts("OK!"); else puts("FAILED");
    free(arr);
}