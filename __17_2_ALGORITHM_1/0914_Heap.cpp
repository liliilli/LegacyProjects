#include <stdio.h>

#define MIN(__A__, __B__) (__A__ > __B__) ? __B__ : __A__
#define ARR_SIZE(__A__) sizeof(__A__) / sizeof(__A__[0])
#define SWAP(__TYPE__, __A__, __B__) { \
        __TYPE__ temp = *__A__; *__A__ = *__B__; *__B__ = temp; \
    }
#define PRINT(__STRING__, __VALUE__) printf("%s : %d\n", __STRING__, __VALUE__)
#define TRAVELSE(__A__, __B__, __N__) \
    for (int i = __A__; i < __B__; ++i) printf("%d ", __N__[i]); \
    printf("\n");

//#define DEBUG

void build_heap(int[], int, int);
void heapify(int*, int);
void heapsort(int[]);

int size = 0;
int main() {
    int array[] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
    size = ARR_SIZE(array);
    heapsort(array);

    TRAVELSE(0, ARR_SIZE(array), array);
}

void heapify(int* array, int index) {
    int left    = (2 * index) + 1;
    int right   = 2 * (index + 1);

    int lst_index   = index;
    if (left < size && array[left] > array[index])
        lst_index = left;
    if (right < size && array[right] > array[lst_index])
        lst_index = right;

    if (lst_index != index) {
        SWAP(int, &array[index], &array[lst_index]);
        heapify(array, lst_index);
    }
}

void build_heap(int array[], int i_first, int i_end) {
    int arr_size = i_end - i_first + 1;
    for (int i = arr_size / 2; i >= 0; --i)
        heapify(array, i);
}

void heapsort(int array[]) {
    build_heap(array, 0, size - 1);

    for (int i = size - 1; i > 0; --i) {
        SWAP(int, &array[0], &array[i]);
        --size;
        heapify(array, 0);
    }
}

