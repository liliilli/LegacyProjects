#include <iostream>
#include <stack>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    auto number = 0; cin >> number;
    std::string str;
    for (auto i = 0; i < number; ++i) {
        cin >> str; stack<char> stk;
        for (const auto& chr : str) stk.push(chr);

        auto count = 0;
        auto check_brace = 0;
        auto check = false;

        while (true) {
            // First
            if (stk.top() == ')') { ++check_brace; ++count; } stk.pop();
            // Body
            while (stk.size() != 1) {
                if (stk.top() == ')') { ++count; } else { --count; } stk.pop();
                if (count < 0) break;
            }
            if (count < 0) break;

            // End 
            if (stk.top() == '(') { ++check_brace; --count; } stk.pop();
            if (check_brace == 2 && count == 0) check = true;
            break;
        }

        cout << (check ? "YES\n" : "NO\n");
    }
}
