#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    auto T = 0; cin >> T;
    queue<int> num_queue;
    for (decltype(T) i = 0; i < T; ++i) {
        std::string command; cin >> command;
        if (command == "push") {
            auto value = 0; cin >> value;
            num_queue.push(value);
        }
        else if (command == "front") {
            if (num_queue.empty()) cout << "-1\n";
            else cout << num_queue.front() << '\n';
        }
        else if (command == "back") {
            if (num_queue.empty()) cout << "-1\n";
            else cout << num_queue.back() << '\n';
        }
        else if (command == "size") 
            cout << num_queue.size() << '\n';
        else if (command == "empty")
            cout << (num_queue.empty() ? "1\n" : "0\n");
        else if (command == "pop") {
            if (num_queue.empty()) cout << "-1\n";
            else {
                cout << num_queue.front() << '\n';
                num_queue.pop();
            }
        }

    }
}
