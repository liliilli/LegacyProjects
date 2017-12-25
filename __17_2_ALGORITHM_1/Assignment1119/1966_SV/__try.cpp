#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int id;
    int priority;
    Node(int id, int priority) : id(id), priority(priority) {};
};

int main() {
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    auto T = 0; cin >> T;
    for (decltype(T) i = 0; i < T; ++i) {
        auto docu_num = 0, check_id = 0; cin >> docu_num >> check_id;
        vector<Node> node_arr; node_arr.reserve(docu_num);

        for (auto j = 0; j < docu_num; ++j) {
            auto value = 0; cin >> value;
            node_arr.push_back(Node(j, value));
        }

        auto comp = [](const Node& lhs, const Node& rhs) {
            return lhs.priority >= rhs.priority;
        };
    
        make_heap(node_arr.begin(), node_arr.end(), comp);
        sort_heap(node_arr.begin(), node_arr.end(), comp);

        for (const auto& item : node_arr) {
            cout << item.priority << "/" << item.id << " ";
        }
        cout << '\n';
    }
}