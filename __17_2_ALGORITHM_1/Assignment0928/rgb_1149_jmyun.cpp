#include <stdio.h>
#define min(a, b) ((a > b) ? b : a)

int main() {
    freopen("rgb_input.txt", "r", stdin);
    int house_count; scanf("%d\n", &house_count);

    int cost_r = 0, cost_g = 0, cost_b = 0;

    int scan_r = 0, scan_g = 0, scan_b = 0;
    for (int i = 0; i < house_count; ++i) {
        scanf("%d %d %d", &scan_r, &scan_g, &scan_b);
        scan_r += min(cost_g, cost_b);
        scan_g += min(cost_r, cost_b);
        scan_b += min(cost_r, cost_g);

        cost_r = scan_r; cost_g = scan_g; cost_b = scan_b;
    }

    printf("%d\n", min(cost_r, min(cost_g, cost_b)));
    return 0;
}