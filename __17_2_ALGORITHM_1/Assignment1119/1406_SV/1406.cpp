#include <iostream>
#include <string>
using namespace std;

struct Node {
    char chr; Node* next = nullptr; Node* back = nullptr;
    Node(const char chr) : chr(chr) {};
};

struct Line {
    Node    dummy = Node('1');
    Node*   first = nullptr; Node* end = nullptr; Node* cursor = &dummy;
    void move_left()    { if (cursor != &dummy) cursor = cursor->back; }
    void move_right()   { if (cursor != end)    cursor = cursor->next; }
    void connect_dummy(Node* node) { dummy.next = node; node->back = &dummy; }
    void connect_each(Node* lhs, Node* rhs) { lhs->next = rhs; rhs->back = lhs; }

    void add(Node* const node) {
        if (!first) { connect_dummy(node); end = first = node; } // Nothing exist.
        else { // Something exist.
            if (cursor == &dummy) { // cursor is on dummy (|abcd)
                connect_each(node, first); connect_dummy(node); first = node; 
            } else if (!cursor->next) { // cursor is on end (abcd|)
                connect_each(cursor, node); end = node; 
            } else { // cursor in on center (ab|cd)
                connect_each(node, cursor->next); connect_each(cursor, node); 
            }
        }

        move_right();
    }

    void remove() {
        if (cursor != &dummy) { // if not (|abcd)
            auto temp = cursor;
            if (temp->back == &dummy) { // if cursor is next of dummy.
                if (!temp->next) { // if (a|)
                    dummy.next = first = end = nullptr;                           
                } else { // if (a|bcd)
                    connect_dummy(temp->next); first = temp->next;
                }
            } else if (!temp->next) { // if (abcd|)
                temp->back->next = nullptr; end = temp->back;
            } else { // if (ab|cd... etc)
                connect_each(temp->back, temp->next); temp->next;
            }

            move_left();
            delete temp;
        }
    }

    void print() {
        auto node = first;
        while (node) { cout << node->chr; node = node->next; } cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    std::string str; cin >> str;
    Line line;
    for (const auto& chr : str) { line.add(new Node(chr)); }
    
    auto count = 0; cin >> count;
    for (int i = 0; i < count; ++i) {
        char command; cin >> command;
        switch (command) {
        case 'P':
            char value; cin >> value;
            line.add(new Node(value));
            break;
        case 'L': line.move_left(); break;
        case 'D': line.move_right(); break;
        case 'B': line.remove(); break;
        }
    }

    line.print();
}