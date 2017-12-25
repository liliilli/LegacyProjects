#include <stdio.h>
//#define DEBUG

#define MIN(__A__, __B__) (__A__ > __B__) ? __B__ : __A__
#define ARR_SIZE(__A__) sizeof(__A__) / sizeof(__A__[0])
#define SWAP(__TYPE__, __A__, __B__) { \
        __TYPE__ temp = *__A__; *__A__ = *__B__; *__B__ = temp; \
    }
#define TRAVELSE(__A__, __B__, __N__) \
    for (int i = __A__; i < __B__; ++i) printf("%d ", __N__[i]); \
    printf("\n");

#ifdef DEBUG
#define PRINT(__STRING__, __VALUE__) printf("%s : %d\n", __STRING__, __VALUE__)
#endif

int get_partition(int array[], int i_start, int i_end);
void quick_sort(int array[], int i_start, int i_end);

int main() {
    int array[] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
    //int array[] = { 5, 2, 4, 3, 1, 7, 6 };
    int size = ARR_SIZE(array);
    quick_sort(array, 0, size - 1);

    TRAVELSE(0, size, array);
}

int get_partition(int array[], int i_start, int i_end) {
    int i_pre = i_start - 1;
    for (int i = i_start; i < i_end; ++i) {
        if (array[i] < array[i_end]) {
            i_pre += 1;
            SWAP(int, &array[i_pre], &array[i]);
        }
    }

    i_pre += 1;
    SWAP(int, &array[i_pre], &array[i_end]);
    return i_pre;
}

void quick_sort(int array[], int i_start, int i_end) {
    if (i_start < i_end) {
        int sep = get_partition(array, i_start, i_end);
        quick_sort(array, i_start, sep - 1);
        quick_sort(array, sep + 1, i_end);
    }
}