#include <iostream>
#include <vector>
#define max(__A__, __B__) (__A__ > __B__) ? __A__ : __B__

std::vector<unsigned> _score(301);
std::vector<unsigned> _max(301);
unsigned find(const int i, const int cnt) {
    switch (cnt) {
    case 1:
        if (_max[i] > 0) return _max[i];
        if (i == 1) return _score[1];
        if (i == 2) return _score[2] + _score[1];
        else {
            unsigned _max = max(find(i - 2, 1), find(i - 1, 2));
            return _score[i] + _max;
        }
    case 2:
        if (i == 2) return _score[2];
        else return _score[i] + find(i - 2, 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    unsigned int arr_count; scanf("%d", &arr_count);
    for (int i = 1; i <= arr_count; ++i) { 
        scanf("%d", &_score[i]); _max[i] = find(i, 1);
    }

    printf("%d\n", _max[arr_count]);
}