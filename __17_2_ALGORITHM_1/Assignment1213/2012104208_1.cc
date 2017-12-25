#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

template <typename _Ty>
inline void initialize(vector<vector<_Ty>>& bidim_array, const unsigned size) {
    for (auto& row : bidim_array) { row = vector<_Ty>(size); }
}

const auto double_dirty = 2;
const auto dirty = 1;
const auto clean = 0;

struct Item {
    const unsigned  id, weight;
    const float     value;
    Item(unsigned id, unsigned weight, float value) : 
        id(id), weight(weight), value(value) {};
    Item() : id(0), weight(87654321), value(0.f) {};
};

int main() {
    ios_base::sync_with_stdio(false); // Fast cin & cout
    // freopen("prob_1_input.txt", "r", stdin);

    unsigned backpack_max = 0;
    vector<Item> item_list(1);

    unsigned id = 0;
    while (true) {
        unsigned weight, value;
        std::cin >> weight >> value;

        if (value == -1) { backpack_max = weight; break; } 
        else {
            id += 1;
            // 노드를 두개씩 넣는다.
            item_list.push_back(Item(id, weight, value));
            item_list.push_back(Item(id, weight, value));
        }
    };

    auto item_num = 2 * id;
    vector<vector<int>> cache_value(item_num + 1);
    initialize(cache_value, 2 * backpack_max + 1);

    vector<vector<int>> cache_flag(item_num + 1);
    initialize(cache_flag, 2 * backpack_max + 1);

    vector<vector<bool>> check_flag(item_num + 1);
    initialize(check_flag, 2 * backpack_max + 1);

    // ************************************************************************
    // More complicated 0/1 Knapsack procedure
    // ************************************************************************
    for (auto y = 1u; y <= item_num; ++y) {
        for (auto x = 0u; x <= 2 * backpack_max; ++x) {
            auto& target    = cache_value[y][x];
            auto t_weight   = item_list[y].weight;
            auto up_value   = cache_value[y - 1][x];

            // If item_list[y] 의 weight 가 x (무게) 보다 클 때
            if (t_weight > x) {
                target = up_value;
                cache_flag[y][x] = cache_flag[y - 1][x];
            }
            // If item_list[y] 의 weight 가 x (무게) 보다 작거나 같을 때 (복잡)
            else if (t_weight <= x) {
                auto t_value = item_list[y].value;
                auto ref_value = t_value + cache_value[y - 1][x - t_weight];
                auto ref_flag = cache_flag[y - 1][x - t_weight];

                // Clean (0.5 노드가 끼어있지 않을 경우에)
                if (ref_flag == clean) {
                    // 위와 이전 + value 을 비교한다. 만약 ref_value 가 크면...
                    if (ref_value > up_value) { // Clean 하기 때문에 항상 Dirty 이다.
                        target = ref_value;
                        cache_flag[y][x] = dirty;
                        check_flag[y][x] = true;
                    }
                    else {
                        target = up_value;
                        cache_flag[y][x] = cache_flag[y - 1][x];
                    }
                }
                // Dirty (하나라도 0.5 노드가 끼어 있을 경우에)
                else if (ref_flag == dirty) {
                    if (ref_value > up_value) { // 위와 이전 + value 을 비교한다.
                        target = ref_value;
                        cache_flag[y][x] = double_dirty;
                        check_flag[y][x] = true;
                    }
                    else if (ref_value == up_value) {
                        if (cache_flag[y - 1][x] == clean)
                            target = up_value;
                        else { // 바로 위가 Clean 하지 않다면 왼쪽 것을 계속 받는다.
                            target = ref_value;
                            cache_flag[y][x] == double_dirty;
                        }
                    }
                    else {
                        target = up_value;
                        cache_flag[y][x] = cache_flag[y - 1][x];
                    }
                } else { // Ref Flag 가 Double Dirty 할 경우에만
                    // 만약 Dirty Node 에 Dirty node가 끼어서 Clean 이 될 수 있다면
                    if ((y / 2 != (y - 1) / 2) && (ref_value >= up_value)) {
                        target = ref_value;
                        cache_flag[y][x] = clean;
                        check_flag[y][x] = true;
                    } else { 
                        target = up_value;
                        cache_flag[y][x] = cache_flag[y - 1][x];
                    }
                }
            }
        }
    }

    // ************************************************************************
    // Reverse travalse to check what items we pick up
    // ************************************************************************
    vector<unsigned> picked_item(item_num + 1);

    auto x = 2 * backpack_max;
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
        case 2: std::cout << item_list[i].id << ' ';        break;
        case 1: std::cout << item_list[i].id << "x0.5 ";    break;
        }
    }   

    cout << setprecision(3) << 
        static_cast<float>(cache_value[item_num][2 * backpack_max]) / 2.f << '\n';
    return 0;
}
