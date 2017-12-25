#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    freopen(argv[1], "r", stdin); // 파일 받기

    // 받아서
    int arr_size = 0;
    scanf("%d", &arr_size);

    // 배열을 만들어준다..
    // map_2 배열은 없으며, map_2 의 요소를 받는 즉시,
    // OR 연산을 수행할 것임
    int* map_1 = (int*)malloc(arr_size * sizeof(int));
    for (int i = 0; i < arr_size; ++i) {
        scanf("%d", &map_1[i]);
    }

    // 받은 후에, map_2 에 대한 인자 받기를 수행한다.
    for (int i = 0; i < arr_size; ++i) {
        int value;
        scanf("%d", &value);

        // OR 연산
        map_1[i] |= value;
        // printf("%d", map_1[i]);
        
        // 캐릭터를 받는다.
        // true / false 이냐에 따라서 # 와 공백을 넣는다.
        printf("|");
        for (int j = 0; j < arr_size; ++j) {
            int _bit = 1 << (arr_size - j - 1);
            int _res = map_1[i] & _bit;
            printf("%c", (_res > 0 ? '#' : ' '));
            // map_1[i] 의 최상위를 하나하나씩 지워 나간다.
            map_1[i] -= _res;
        }
        printf("|\n");
    }

    free(map_1);
    return 0;
}