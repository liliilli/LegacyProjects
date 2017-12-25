#include <stdio.h>
#define INF 999999
#define min(a, b) (a > b) ? b : a

int main() {
    freopen("rgb_street_input.txt", "r", stdin);
    int house_count; scanf("%d\n", &house_count);

    int max_index = house_count + 1;
    int sum[1010][3] = { 0 };   
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j < max_index; ++j)
            sum[j][i] = INF;

    int cost[1010][3] = { 0 };
    for (int i = 0; i < house_count; ++i)
        for (int j = 0; j < 3; ++j)
            scanf("%d", &cost[i][j]);

    // process
    for (int cur = 1; cur < max_index; ++cur)
        for (int prev = 0; prev < 3; ++prev)
            for (int rgb = 0; rgb < 3; ++rgb) {
                if (prev != rgb)
                    sum[cur][rgb] = min(sum[cur][rgb], sum[cur-1][prev] + cost[cur-1][rgb]);
            }

    int min_sum = INF;
    for (int i = 0; i < 3; ++i)
        min_sum = min(min_sum, sum[house_count][i]);
    
    printf("%d\n", min_sum);

    return 0;
}