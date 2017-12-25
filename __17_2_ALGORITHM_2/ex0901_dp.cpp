#include <stdio.h>
#define min(a, b) (a > b) ? a : b

int dp_coin(int);

int main() {
    int input;
    
    while (true) {
        // scanf("%d", &input);
        dp_coin(12);
    }
}

int dp_coin(int n) {
    const int size = n + 1;
    int money[size] = {0, };
    int array[4] = { 1, 2, 6, 8 };

    auto one = 0, two = 0, six = 0, eight = 0;
    for (int index = 1; index <= n; ++index) {
        auto m = money[index - 1];

        if (index >= 1)
            one += 1;

        auto kind = 2;
        if (index >= kind) {
            if (m > money[index - kind]) {
                m = money[index - kind]; 
            } 
        }

        kind = 6;
        if (index >= kind) {
            if (m > money[index - kind]) {
                m = money[index - kind]; 
            } 
        }

        kind = 8;
        if (index >= kind) {
            if (m > money[index - kind]) {
                m = money[index - kind]; 
            } 
        }

        money[index] = m + 1;
    }

    printf("N: %d\n", money[n]);
    return money[n];
}