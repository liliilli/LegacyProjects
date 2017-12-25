#include <iostream>
#include <vector>

std::vector<unsigned> _case(11);
int find(const int i) {
    if (_case[i] > 0 || (0 <= i && i <= 2)) return _case[i];
    else return _case[i] = find(i - 1) + find(i - 2) + find(i - 3);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    _case[0] = 1; _case[1] = 1; _case[2] = 2;

    int test_case; std::cin >> test_case;
    for (int i = 0; i < test_case; ++i) {
        int _input; std::cin >> _input;
        find(_input);
        printf("%d\n", _case[_input]);
    }
}