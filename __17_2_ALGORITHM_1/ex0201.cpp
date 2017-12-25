#include <iostream>

void print_lines(const int);

int main() {
    int input_value;
    printf("Enter the number of lines : ");
    scanf("%d", &input_value);

    print_lines(input_value);
    return 0;
}

void print_lines(const int lines) {
    bool is_even = (lines % 2 == 0) ? true : false;
    bool is_ascend = true;

    int separate_line = lines / 2;
    int numbers_display, loop_count, space_count;

    for (int present_line = 0; present_line < lines; ++present_line) {
        if (is_ascend && present_line >= separate_line) is_ascend = false;

        if (is_ascend) {
            numbers_display = 2 * present_line + 1;
            space_count = separate_line - present_line - ((is_even) ? 1 : 0);
        } else {
            numbers_display = 2 * (lines - present_line) - 1;
            space_count = present_line - separate_line;
        }

        loop_count = numbers_display / 9;
        numbers_display %= 9;

        for (int i = space_count; i > 0; --i)       printf(" ");
        for (int i = numbers_display; i > 0; --i)   printf("%d",i);
        for (int i = loop_count; i > 0; --i)        printf("987654321");
        printf("\n");
    }
}