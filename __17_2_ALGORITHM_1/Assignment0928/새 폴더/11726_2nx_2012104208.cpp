#include <iostream>
#include <vector>

std::vector<unsigned> _arr(1001);
unsigned find(const int i) {
    if (_arr[i] == 0) _arr[i] = (find(i - 1) + find(i - 2)) % 10007;
    
    return _arr[i];
}

int main() {
    std::ios_base::sync_with_stdio(false);

    _arr[1] = 1; _arr[2] = 2;
    unsigned int i; scanf("%d", &i);

    unsigned res = find(i);
    printf("%d\n", res);
}