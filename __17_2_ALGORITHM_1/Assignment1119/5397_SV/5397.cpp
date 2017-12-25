#include <iostream>
#include <cstdio>
using namespace std;

struct Node {
    char chr; Node* next = nullptr; Node* back = nullptr;
    Node(const char chr) : chr(chr) {};
};

struct Line {
    Node    dummy = Node('1');
    Node*   first = nullptr; Node* end = nullptr; Node* cursor = &dummy;
    void move_left()    { if (cursor != &dummy) cursor = cursor->back; }
    void move_right()   { if (cursor != end && dummy.next) cursor = cursor->next; }
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
        while (node) { printf("%c", node->chr); node = node->next; } 
        printf("\n");
    }

    ~Line() { // Destructor
        auto temp = end;
        while (temp && temp != &dummy) {
            auto temp_remove = temp;
            temp = temp->back;
            delete temp_remove;
        }
    }
};

int main() {
    auto T = 0; scanf("%d\n", &T);
    for (decltype(T) i = 0; i < T; ++i) {
        Line line;

        while (true) { 
            char chr; scanf("%c", &chr); 
            if (chr == '\n' || feof(stdin)) break;

            switch (chr) {
            case '<': line.move_left(); break;
            case '>': line.move_right(); break;
            case '-': line.remove(); break;
            default:
                line.add(new Node(chr));
                break;
            }
        }
        
        line.print();
    }
}