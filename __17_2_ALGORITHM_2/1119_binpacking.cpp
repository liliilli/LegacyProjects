#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
// Tourament

const int INT_INF = numeric_limits<int>::max();
const std::string FILE_NAME = "input_bin.txt";

// Player 수, 인데 지금은 32로 하자.. 2^k 승.
// 컨테이너 사이즈가 20, 중간에가 들어오는 bin 수.

// Tournament and Chapter 9 Bin 어쩌구 문제. 및 hwp 파일 참고.
// 20일때, 21일때, 100개일때 검사한다.
inline void print(const vector<int>& container);

// Main 
int main() {
    std::ios_base::sync_with_stdio(false);
    freopen(FILE_NAME.c_str(), "r", stdin);

    int player_number, node_number, container_capacity;
    cin >> player_number >> node_number >> container_capacity;

    // 0 번째는 더미로 돌린다.
    vector<int> player_containers(player_number + 1, container_capacity); //player_number + 1(DUMMY)
    vector<int> max_pindex_tree(player_number); // player_number - 1 + 1(DUMMY)

    // Value Setting to make max_capacity_tree;
    auto s_sublast_number = pow(2, static_cast<int>(ceil(log2(player_number) - 1)));
    auto lowest_ext_node = static_cast<int>(2 * ((player_number - 1) - (s_sublast_number - 1)));
    auto offset = 2 * s_sublast_number - 1;

    // vector resize fill up with last nodes (player_containers);
    max_pindex_tree.resize(2 * player_number); // player_number - 1 + 1 + player_number
    auto p_index = 1;
    for (int t_i = 2 * player_number - lowest_ext_node; t_i < 2 * player_number; ++t_i) {
        max_pindex_tree[t_i] = p_index; ++p_index;
    }
    for (int t_i = player_number; t_i < 2 * player_number - lowest_ext_node; ++t_i) {
        max_pindex_tree[t_i] = p_index; ++p_index;
    }

    // *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** 
    // 초기 tree setting
    if (player_number % 2 == 0) { // Player Number is even number;
        for (auto k = 1; k <= player_number; k += 2) {
            auto t_index = static_cast<int>(0);

            if (k <= lowest_ext_node)
                t_index = static_cast<int>((k + offset) / 2);
            else
                t_index = (k - lowest_ext_node + player_number - 1) / 2;

            max_pindex_tree[t_index] = k;
        }
    }
    else { // Player number is odd number;
        auto t_index = static_cast<int>(0);

        for (auto k = 1; k <= lowest_ext_node; k += 2) {
            t_index = static_cast<int>((s_sublast_number + (player_number - 1) - (lowest_ext_node / 2) + k) / 2);
            max_pindex_tree[t_index] = k;
        }

        for (auto k = lowest_ext_node + 2; k <= player_number; k += 2) {
            t_index = (k - lowest_ext_node + player_number - 1) / 2;
            max_pindex_tree[t_index] = k;
        }
    }

    for (auto t_index = (player_number - 1) / 2; t_index > 0; --t_index) {
        auto lhs_index = t_index * 2;
        max_pindex_tree[t_index] = max_pindex_tree[lhs_index];
    }

    print(max_pindex_tree);

    // *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** 
    // 
    auto array_last_parent = (2 * player_number - 1) / 2;
    for (auto i = 0; i < node_number; ++i) {
        print(player_containers);

        auto node_value = 0; cin >> node_value;

        // *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** 
        // Comparison
        auto t_index = 1;
        //while (t_index <= (player_number - 1) / 2) {
        while (t_index <= array_last_parent) {
            auto lhs_index      = t_index * 2;
            auto p_lhs_index    = max_pindex_tree[lhs_index];

            if (player_containers[p_lhs_index] >= node_value) { 
                t_index = lhs_index; 
            }
            else { 
                auto rhs_index  = lhs_index + 1;
                t_index = rhs_index; 
            }
        }

        // Final Comparison
        auto res_index = max_pindex_tree[t_index];
        player_containers[res_index] -= node_value;

        // *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** 
        // Rebuild max win tree
        if (player_number % 2 == 0) { 
            // Player Number is even number;
            for (auto k = 1; k <= player_number; k += 2) {
                auto t_index = static_cast<int>(0);
                auto lhs = player_containers[k];
                auto rhs = player_containers[k + 1];

                if (k <= lowest_ext_node) {
                    t_index = static_cast<int>((k + offset) / 2);
                }
                else {
                    t_index = (k - lowest_ext_node + player_number - 1) / 2;
                }

                if (lhs < rhs)
                    max_pindex_tree[t_index] = k + 1;
                else
                    max_pindex_tree[t_index] = k;
            }   
        }
        else { 
            // Player number is odd number;
            for (auto k = 1; k <= lowest_ext_node; k += 2) {
                auto lhs = player_containers[k];
                auto rhs = player_containers[k + 1];

                auto t_index = (s_sublast_number + (player_number - 1) - (lowest_ext_node / 2) + k) / 2;
                if (lhs < rhs)  { max_pindex_tree[t_index] = k + 1; }
                else            { max_pindex_tree[t_index] = k; }
            }

            for (auto k = lowest_ext_node + 2; k <= player_number; k += 2) {
                auto lhs = player_containers[k];
                auto rhs = player_containers[k + 1];

                auto t_index = (k - lowest_ext_node + player_number - 1) / 2;
                if (lhs < rhs)  { max_pindex_tree[t_index] = k + 1; }
                else            { max_pindex_tree[t_index] = k; }
            }
        }

        // Common Resorting
        for (auto t_index = (player_number - 1) / 2; t_index > 0; --t_index) {
            auto lhs_index = t_index * 2;
            auto rhs_index = lhs_index + 1;

            auto lhs_value = player_containers[max_pindex_tree[lhs_index]];
            auto rhs_value = player_containers[max_pindex_tree[rhs_index]];

            if (lhs_value < rhs_value)  { max_pindex_tree[t_index] = max_pindex_tree[rhs_index]; }
            else                        { max_pindex_tree[t_index] = max_pindex_tree[lhs_index]; }
        }
    }

    // *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** 
    print(player_containers);
    return 0;
}

inline void print(const vector<int>& container) {
    for (auto& value : container) { cout << setw(2) << value << ' '; } cout << "\n";
}