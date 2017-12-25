#include <iostream>
#include <ctime>
#include <stdlib.h>
#define SUCCESS 0;

int get_random_number(void) { return rand(); } 
bool is_minus(const int value) { return (value < 0) ? true : false; }

int compare_num(const int guess, const int answer);
void guess_it(const int);
int guess_number(const int value, const int present, const bool is_ascend, const bool init);
void init() { srand(time(NULL)); }

static const int LESS_THAN = 1;
static const int EQUAL = 0;
static const int BIGGER_THAN = -1;
static int search_count = 0;
static bool minus;

int main() {
    init();

    int answer;
    std::cin >> answer;

    printf("Answer = ? %d\n", answer);

    minus = is_minus(answer);
    if (minus) 
        answer *= -1;
    std::cout << answer << std::endl;

    guess_it(answer);
    if (minus)
        answer *= -1;
    printf("Found %d in %d guesses\n", answer, search_count);

    return SUCCESS;
}


int compare_num(const int guess, const int answer) {
    int value = 0;

    ++search_count;
    if (minus)
        printf("Guess %d: -%d\n", search_count, guess);
    else
        printf("Guess %d: %d\n", search_count, guess);
    
    return (guess < answer) ? BIGGER_THAN : ((guess > answer) ? LESS_THAN : 0);
}

void guess_it(const int answer) {
    int backup          = 0;
    int guessed_value   = 0;
    int flag            = 0;

    flag = compare_num(guessed_value, answer);
    if (flag == EQUAL) return;

    bool is_ascend = true;
    bool is_init = true;
    while (true) {
        guessed_value = guess_number(backup, guessed_value, is_ascend, is_init);

        flag = compare_num(guessed_value, answer);
        if (flag == LESS_THAN) {
            if (is_init)
                is_init = false;

            is_ascend = false;
        } else if (flag == BIGGER_THAN) {
            if (is_init) 
                backup = guessed_value;

            is_ascend = true;
        } else
            break;

        if (!is_init) backup /= 2;
    }
}

int guess_number(const int value, const int present, const bool is_ascend, const bool init) {
    if (value == 0) return 2;
    else if (init) return value * 2;

    if (is_ascend) {
        return present + (int)(value);
    } else {
        return present - (int)(value);
    }
}