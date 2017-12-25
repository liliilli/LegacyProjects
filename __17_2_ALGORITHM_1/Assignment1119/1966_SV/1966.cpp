#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int id; int priority;
    Node(int id, int priority) : id(id), priority(priority) {};
};

int main() {
    ios_base::sync_with_stdio(false);
    auto T = 0; cin >> T;
    for (decltype(T) i = 0; i < T; ++i) {
        auto docu_num = 0, check_id = 0; cin >> docu_num >> check_id;
        vector<Node> node_queue; node_queue.reserve(docu_num);        

        for (auto j = 0; j < docu_num; ++j) { // N^2
            auto value = 0; cin >> value; node_queue.push_back(Node(j, value));
        }

        auto index = 0; auto size = docu_num; 
        while (true) {
            auto check_flag = false; 

            auto save_size = size;
            while (!check_flag) {
                auto node = node_queue[0]; auto check = false;

                for (auto k = 1; k < size; ++k) {
                    auto& item = node_queue[k];
                    if (item.id != node.id && item.priority > node.priority) {
                        node_queue.erase(node_queue.cbegin());
                        node_queue.push_back(node);
                        check = true;
                        break;
                    }
                }

                --size; 
                if (!check) check_flag = true;
            }
            size = save_size;

            if (node_queue.cbegin()->id == check_id) {
                cout << index + 1 << '\n'; break;
            } else {
                node_queue.erase(node_queue.cbegin());
                ++index; --size;
            }
        }
    }
}