#include <iostream>

void print_lines(const int);

int main() {
    int input_value;
    printf("Enter the number of lines : "); 
    scanf("%d", &input_value);

    print_lines(input_value);
    return 0;
}

void display_numbers(const int numbers_display) {
    int count = (numbers_display + 1) / 2;
    int loop_count = count / 9;
    count %= 9;

    for (int i = 0; i < loop_count; ++i)    printf("123456789");
    for (int i = 1; i <= count ; ++i)       printf("%d", i);

    count = numbers_display - (count + loop_count * 9);
    loop_count = count / 9;

    for (int i = count % 9; i > 0; --i)     printf("%d", i);
    for (int i = 0; i < loop_count; ++i)    printf("987654321");
}

void print_lines(const int lines) {
    bool is_even = (lines % 2 == 0) ? true : false;
    bool is_ascend = true;

    int separate_line = lines / 2;
    int numbers_display = 0, space_count = 0;

    for (int present_line = 0; present_line < lines; ++present_line) {
        if (is_ascend && present_line >= separate_line) is_ascend = false;

        if (is_ascend) {
            numbers_display = 2 * present_line + 1;
            space_count = separate_line - present_line - ((is_even) ? 1 : 0);
        } else {
            numbers_display = 2 * (lines - present_line) - 1;
            space_count = present_line - separate_line;
        }

        for (int i = 0; i < space_count; ++i) printf(" ");
        display_numbers(numbers_display);
        printf("\n");
    }
}