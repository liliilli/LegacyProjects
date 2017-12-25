#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue {
    int size = 0;
    Node* front = nullptr;
    Node* end = nullptr;

    void push(Node* node) {
        if (front == nullptr)
            front = end = node;
        else
            end->next = node;
        
        size += 1;
    }

    void pop() {
        if (size > 0) {
            Node* temp = front;
            front = front->next;
            free(temp);
            size -= 1;
        }
    }

    Node* front() { return front; }
};

struct Edge {
    int dst = 0;
    Edge* next = nullptr;
}

struct Node {
    bool is_visited = false;
    int distance = 0;
    Node* parent = nullptr; 
    Node* next = nullptr;

    Edge* e_first = nullptr; Edge* e_end = nullptr;
};

int main() {
    
}
