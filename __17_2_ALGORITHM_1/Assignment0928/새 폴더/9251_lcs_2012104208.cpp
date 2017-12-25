#include <iostream>
#include <string>
#include <vector>
#define max(__A__, __B__) (__A__ > __B__) ? __A__ : __B__

int main() {
    std::ios_base::sync_with_stdio(false);
    std::string A, B;
    std::getline(std::cin, A); std::getline(std::cin, B);
    unsigned a_sz = A.size(); unsigned b_sz = B.size();

    std::vector<std::vector<int>> _arr(a_sz + 1); // 초기화
    for (auto& _i : _arr) { _i = std::vector<int>(b_sz + 1); }

    unsigned max_lcs = 0;
    for (int i = 0; i <= a_sz; ++i) { // 세로 축
        for (int j = 0; j <= b_sz; ++j) { // 가로 축
            if (i == 0 || j == 0) _arr[i][j] = 0; // 0행, 0열은 0으로 초기화
            else { // 아니라면? 상, 좌측 원소의 최댓값 + 조건으로 갱신
                if (A[i - 1] == B[j - 1]) { 
                    _arr[i][j] += _arr[i-1][j-1] + 1; 
                    max_lcs = max(max_lcs, _arr[i][j]); 
                } else {
                    _arr[i][j] = max(_arr[i][j - 1], _arr[i - 1][j]);
                }
            }
        }
    }

    printf("%d\n", max_lcs);
}