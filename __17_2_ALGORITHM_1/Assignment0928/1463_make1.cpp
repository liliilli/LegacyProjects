#include <iostream>
#include <vector>
#define min(__A__, __B__) (__A__ < __B__) ? __A__ : __B__

std::vector<unsigned> _count(1000001);
unsigned cal(const int i) {
    if (_count[i] > 0) return _count[i];

    // 디폴트도 아니고, 메모이제이션도 안되있으면
    int _mod3 = i % 3; int _mod2 = i % 2;

    if (_mod3 == 0 && _mod2 == 0) {
        unsigned __ = min(cal(i / 3), cal(i / 2));
        unsigned _val = min(cal(i - 1), __);
        return 1 + _val;
    }
    else if (_mod3 == 0) {
        unsigned _val = min(cal(i / 3), cal(i - 1));
        return 1 + _val;
    }
    else if (_mod2 == 0) {
        unsigned _val = min(cal(i / 2), cal(i - 1));
        return 1 + _val;
    }
    else return 1 + cal(i - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    unsigned int arr_count; scanf("%d", &arr_count);
    _count[2] = _count[3] = 1;
    for (int i = 4; i <= arr_count; ++i) { 
        _count[i] = cal(i);
    }
    printf("%d\n", _count[arr_count]);
}