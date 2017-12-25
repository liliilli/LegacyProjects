#include <iostream>
#include <ctime>
#include <stdlib.h>
#define SUCCESS 0;

int get_random_number(const int);
int compare_num(const int guess, const int answer);
int guess_number(const int, const int);

static const int LIMIT = 1000;
static const int LESS_THAN = 1;
static const int BIGGER_THAN = -1;
static int search_count = 0;

int main() {
    srand(time(NULL));
    int answer = 1;
    // int answer = get_random_number(LIMIT) + 1;

    printf("Answer = ? %d\n", answer);
    
    int end             = LIMIT;
    int start           = 1;
    int guessed_value   = 0;
    int flag            = 0;
    while (true) {
        guessed_value = guess_number(end, start);

        flag = compare_num(guessed_value, answer);
        if (flag == LESS_THAN)
            end = guessed_value;
        else if (flag == BIGGER_THAN)
            start = guessed_value;
        else
            break;
    }

    printf("Found %d in %d guesses\n", answer, search_count);

    return SUCCESS;
}

int get_random_number(const int number) { return rand() % number; } 

int compare_num(const int guess, const int answer) {
    int value = 0;

    ++search_count;
    printf("Guess %d: %d\n", search_count, guess);
    
    return (guess < answer) ? BIGGER_THAN : ((guess > answer) ? LESS_THAN : 0);
}

int guess_number(const int end, const int start) {
    return static_cast<int>((end + start) / 2);
}