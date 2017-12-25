#include <stdio.h>
#include <stdlib.h>
#define INIT 0

void process() {
    // 문자열로 받도록 한다. 쭈욱
    char string[16];
    fgets(string, 16, stdin);
    char* str = string; // string 의 포인터 참조 위치

    int val_arr[4] = {INIT, INIT, INIT, INIT};

    // FSM 을 만든다.
    char fsm = 0; // 0 숫자, 1 SDT, 2 Option
    int i = 1;
    while (i < 4) {
        switch (fsm) {
        case 0: // 숫자를 받는 곳.
            if (*str == '1' && *(str + 1) == '0') { //_got == '1', _got+1 == '0'
                val_arr[i] = 10; // 10 을 갱신한다.
                str++; // 포인터를 옮긴다.
            } else { val_arr[i] = *str - '0'; }

            fsm = 1; ++str; // fsm 을 전환하고, 포인터 위치를 옮긴다.
            break;
        case 1: // S, D, T 을 받는 곳.
            switch (*str) { // S 이면 아무것도 하지 않는다.
            case 'D': // 2 제곱
                val_arr[i] *= val_arr[i];
                break;
            case 'T': // 3 제곱
                int temp = val_arr[i] * val_arr[i];
                val_arr[i] *= temp; 
                break;
            }
            str++;

            if (*str == '*' || *str == '#') // 만약, 옵션이 있으면
                fsm = 2; // fsm 상태를 2로 전환한다.
            else { // 아니면 다시 숫자를 받도록 한다. index 증가.
                fsm = 0; i++;
            } 
            break;
        case 2: // * 또는 # 만 거치는 곳
            if (*str == '*') { // * 카드라면
                val_arr[i-1] *= 2; val_arr[i] *= 2;
            } else // # 카드라면
                val_arr[i] *= -1;

            str++; i++; fsm = 0;
            break;
        }
    }
    
    printf("%d\n", val_arr[1] + val_arr[2] + val_arr[3]);
}

int main(int argc, char* argv[]) {
    freopen(argv[1], "r", stdin); // 파일 받기
    process();
    return 0;
}