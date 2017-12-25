#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    auto operand_number = 0;        cin >> operand_number;
    std::string equation_string;    cin >> equation_string;
    
    vector<int> operand_list; operand_list.reserve(operand_number);
    for (int i = 0; i < operand_number; ++i) {
        auto value = 0; cin >> value;
        operand_list.push_back(value);
    }

    // Proceed
    stack<double> storage;
    for (const auto& chr : equation_string) {
        double lhs, rhs; double value = 0;
        switch(chr) {
        case '+':
            rhs = storage.top(); storage.pop(); lhs = storage.top(); storage.pop();
            value = lhs + rhs; storage.push(value);
            break;
        case '-':
            rhs = storage.top(); storage.pop(); lhs = storage.top(); storage.pop();
            value = lhs - rhs; storage.push(value);
            break;
        case '*':
            rhs = storage.top(); storage.pop(); lhs = storage.top(); storage.pop();
            value = lhs * rhs; storage.push(value);
            break;
        case '/':
            rhs = storage.top(); storage.pop(); lhs = storage.top(); storage.pop();
            value = lhs / rhs; storage.push(value);
            break;
        default:
            storage.push(operand_list[chr - 'A']);
            break;
        }
    }

    cout << fixed << setprecision(2) << storage.top() << '\n';
}
