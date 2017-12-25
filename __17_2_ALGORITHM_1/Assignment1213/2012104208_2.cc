#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

template <typename _Ty>
inline void initialize(vector<vector<_Ty>>& bidim_array, const unsigned size) {
    for (auto& row : bidim_array) { row = vector<_Ty>(size); }
}

const auto LIMIT    = 3;
const auto FILLED   = 2;
const auto NORMAL   = 1;
const auto NONE     = 0;

struct Item {
    const unsigned  id, weight;
    const float     value;
    Item(unsigned id, unsigned weight, float value) : 
        id(id), weight(weight), value(value) {};
    Item() : id(0), weight(87654321), value(0.f) {};
};

int main() {
    ios_base::sync_with_stdio(false); // Fast cin & cout
    // freopen("prob_2_input.txt", "r", stdin);

    unsigned backpack_max = 0;
    vector<Item> item_list(1);

    unsigned id = 0;
    while (true) {
        unsigned weight, value;
        std::cin >> weight >> value;

        if (value == -1) { backpack_max = weight; break; } 
        else {
            id += 1; // 노드를 두개씩 넣는다.
            item_list.push_back(Item(id, weight, value));
            item_list.push_back(Item(id, weight, value));
        }
    };

    auto item_num = 2 * id;
    vector<vector<int>> cache_value(item_num + 1);
    initialize(cache_value, backpack_max + 1);

    vector<vector<int>> cache_flag(item_num + 1);
    initialize(cache_flag, backpack_max + 1);

    vector<vector<bool>> check_flag(item_num + 1);
    initialize(check_flag, backpack_max + 1);

    // ************************************************************************
    // More complicated 0/1 Knapsack procedure
    // ************************************************************************
    for (auto y = 1u; y <= item_num; ++y) {
        for (auto x = 0u; x <= backpack_max; ++x) {
            auto& target    = cache_value[y][x];
            auto t_weight   = item_list[y].weight;
            auto up_value   = cache_value[y - 1][x];

            if (t_weight > x) {
                target = up_value;
                cache_flag[y][x] = cache_flag[y - 1][x];
            }
            // If item_list[y] 의 weight 가 x (무게) 보다 작거나 같을 때 (복잡)
            else if (t_weight <= x) {
                auto t_value    = item_list[y].value;
                auto& t_flag    = cache_flag[y][x];

                auto ref_value  = t_value + cache_value[y - 1][x - t_weight];
                auto ref_flag   = cache_flag[y - 1][x - t_weight];

                auto up_flag    = cache_flag[y - 1][x];

                switch (ref_flag) {
                case NONE: { // 값이 0 일때만 NONE 상태임.
                    if (ref_value > up_value) { 
                        target = ref_value; t_flag = NORMAL; 
                        check_flag[y][x] = true;
                    } else {
                        target = up_value; t_flag = up_flag;
                    }
                }   break;
                case NORMAL: { // 값이 하나라도 갱신이 됬으면 기본 NORMAL
                    if (ref_value > up_value) {
                        target = ref_value;

                        if (y / 2 != (y - 1) / 2) t_flag = FILLED; 
                        else t_flag = NORMAL;
                        
                        check_flag[y][x] = true;
                    } else if (ref_value == up_value) {
                        target = up_value; 
                        switch (up_flag) { 
                        case NORMAL: 
                            t_flag = up_flag; break;
                        case FILLED: case LIMIT: 
                            t_flag = NORMAL; check_flag[y][x] = true; break;
                        }
                    } else {
                        target = up_value; t_flag = up_flag;
                    }
                }   break;
                case FILLED: { // 2개가 됬을 때.
                    if (ref_value > up_value) {
                        // 어차피 전부 LIMIT 가 됨.
                        target = ref_value;
                        t_flag = LIMIT; 
                        check_flag[y][x] = true;
                    } else if (ref_value == up_value) {
                        target = up_value;
                        switch (up_flag) {
                        case NORMAL: case FILLED:   
                            t_flag = up_flag; break;
                        case LIMIT: 
                            t_flag = LIMIT; check_flag[y][x] = true;  break;
                        }
                    } else {
                        target = up_value; t_flag = up_flag;
                    }
                }   break;
                case LIMIT: {
                    // LIMIT 는 ODD 가 될 때만 갱신 가능. EVEN 일 때는 아예 값 갱신이 안됨.
                    if ((y % 2 == 1) && ref_value > up_value) { 
                        target = ref_value; t_flag = ref_flag;
                        check_flag[y][x] = true;
                    } else {
                        target = up_value;
                        t_flag = up_flag;
                    }
                }   break;
                }
            }
        }
    }

    // ************************************************************************
    // Reverse travalse to check what items we pick up
    // ************************************************************************
    vector<unsigned> picked_item(item_num + 1);

    auto x = backpack_max;
    for (auto y = item_num; y > 0; --y) {
        if (check_flag[y][x] == true) {
            x -= item_list[y].weight;
            picked_item[y] += 1;
        }

        if (x <= 0) break;
    }

    // ************************************************************************
    // Print
    // ************************************************************************
    for (auto i = 1u; i <= item_num; i += 2) { 
        auto value = picked_item[i] + picked_item[i + 1];
        switch (value) {
        case 2: std::cout << item_list[i].id << "x2 ";   break;
        case 1: std::cout << item_list[i].id << ' ';    break;
        }
    }   

    std::cout << cache_value[item_num][backpack_max] << '\n';
    return 0;
}
