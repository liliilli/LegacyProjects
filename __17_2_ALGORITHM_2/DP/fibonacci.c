#include <stdio.h>
#define ZERO 0
#define ONE 1
#define INF 999999

int main() {
    FILE* stream = fopen("fibonacci_input.txt", "r");
    int case_count; fscanf(stream, "%d\n", &case_count);

    unsigned int array[2][40 + 1];
    for (int i = 0; i < 41; ++i)
        array[ZERO][i] = array[ONE][i] = INF;
    array[ZERO][0] = 1; array[ONE][0] = 0;
    array[ZERO][1] = 0; array[ONE][1] = 1;

    int max_number = 2;
    for (int i = 0; i < case_count; ++i) {
        int number; fscanf(stream, "%d\n", &number);

        if (array[ZERO][number] == INF) {
            for (int i = max_number; i <= number; ++i) {
                array[ZERO][i] = fibonacci(i, array[ZERO]);
                array[ONE][i]  = fibonacci(i, array[ONE]);
            } 
            max_number = number;
        }

        printf("%d %d\n", array[ZERO][number], array[ONE][number]);
    }

    close(stream);
    return 0;
}

int fibonacci(int index, unsigned int* array) {
    if (array[index] != INF) return array[index];
    else return fibonacci(index - 1, array) + fibonacci(index - 2, array);
}