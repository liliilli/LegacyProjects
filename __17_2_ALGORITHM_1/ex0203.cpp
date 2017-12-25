#include <iostream>
#define LEFT    false
#define RIGHT   true

void print_lines(const int);

int main() {
    int input_value;
    printf("Enter the number of lines : "); 
    scanf("%d", &input_value);

    print_lines(input_value);
    return 0;
}

void display_numbers(int* start_number, const int length, bool direction) {
    if (direction == LEFT) {
        for (int i = length - 1; i >= 0; --i) 
            printf("%d", (i + *start_number) % 9 + 1);
        *start_number += length;
    } else {
        for (int i = 0; i < length; ++i) 
            printf("%d", ((*start_number)++) % 9 + 1);
    }
}

void print_lines(const int lines) {
    bool is_even = (lines % 2 == 0) ? true : false;
    bool is_ascend = true;

    int separate_line = lines / 2;
    int length, space_count;

    int number = 0;
    bool direction = RIGHT;
    for (int present_line = 0; present_line < lines; ++present_line) {
        if (is_ascend && present_line >= separate_line) is_ascend = false;

        if (is_ascend) {
            length = 2 * present_line + 1;
            space_count = separate_line - present_line - ((is_even) ? 1 : 0);
        } else {
            length = 2 * (lines - present_line) - 1;
            space_count = present_line - separate_line;
        }

        for (int i = space_count; i > 0; --i) printf(" ");
        display_numbers(&number, length, direction); printf("\n");

        direction = !direction;
    }
}