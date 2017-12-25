#include <stdio.h>
#include <stack> // 일단 이미 짜여진 걸로 해본다. 그 뒤에
#include <queue> // 그 뒤에 커스텀된 컨테이너를 짜서 넣는다.

// ****************************************************************************
struct LL_Node {
    unsigned id;
    LL_Node* prev;
    LL_Node* next;

    LL_Node(unsigned i) {
        id = i;
        next = prev = nullptr;
    }
};

struct LinkedList {
    LL_Node* first;
    LL_Node* end;

    LinkedList() { first = end = nullptr; }

    void insert(unsigned id) {
        LL_Node* node = new LL_Node(id);

        if (end != nullptr) {
            first->prev = node;
            node->next = first;
            first = node;
        } else { // 암것도 없다면
            first = end = node;
        }
    }

    void print() {
        if (end == nullptr)
            printf("No elements!\n");
        else {
            LL_Node* temp = first;
            while (temp != nullptr) {
                printf("%d ", temp->id);
                temp = temp->next;
            }   
            printf("\n");
        }
    }
};
LinkedList sorted_list;

// *****************************************************************************
struct Edge {
    unsigned destination;
    Edge* next_edge;

    Edge(unsigned i) { 
        destination = i; 
        next_edge = nullptr;
    }
};

struct Node {
    Edge* first;
    Edge* end;
    int is_visited;
    unsigned distance;
    unsigned previous;

    unsigned id;

    Node() {
        first = nullptr;
        end = nullptr;
        is_visited = 0;
        distance = 999999;
        previous = -1;
    }

    void insert(unsigned dst) {
        if (first == nullptr) { // 만약 컨테이너가 공백 상태라면
            first = new Edge(dst);
            end = first;
        } else { // 이미 뭔가가 있다면
            Edge* temp = new Edge(dst);
            end->next_edge = temp;
            end = temp;
        }
    }

    void print_elements() {
        if (first == nullptr)
            printf("No elements!\n");
        else {
            Edge* temp = first;
            while (temp != nullptr) {
                printf("%d, ", temp->destination);
                temp = temp->next_edge;
            }   
            printf("\n");
        }
    }
};
// *****************************************************************************

void dfs_visit(unsigned src, Node* nodes) {
    nodes[src].is_visited = 1;

    Edge* temp = nodes[src].first;
    while (temp != nullptr) {
        auto dst = temp->destination;
        if (nodes[dst].is_visited == 0) {
            nodes[dst].previous = src;
            dfs_visit(dst, nodes);
        }

        temp = temp->next_edge;
    }
    
    nodes[src].is_visited = 2;
    sorted_list.insert(src);
}

void bfs_process(std::queue<Node*>& queue, Node* container) {
    while (!queue.empty()) {
        Node* temp = queue.front();
        Edge* e_temp = temp->first;

        while (e_temp != nullptr) {
            auto dst = e_temp->destination;
            if (container[dst].is_visited == 0) {
                container[dst].is_visited = 1;
                container[dst].distance = temp->distance + 1;
                container[dst].previous = temp->id;
                queue.push(&container[dst]);
            }

            e_temp = e_temp->next_edge;
        }

        queue.pop();
        temp->is_visited = 2;
    }
}

// ****************************************************************************
int main() {
    unsigned node_num, edge_num;
    freopen("bfs_dfs_input.txt", "r", stdin);

    scanf("%d %d", &node_num, &edge_num);
    Node container[node_num + 1]; // 0 은 없는 셈 친다.
    for (int i = 0; i <= node_num; ++i) {
        container[i].id = i;
    }

    // 집어넣는다.
    for (int i = 0; i < edge_num; ++i) {
        unsigned src, dst;
        scanf("%d %d", &src, &dst); // 받는다.
        // insert 한다.
        container[src].insert(dst);
    }

    // 됬네... 그러면 간단한 dfs 부터 시작한다.
    for (int i = 1; i <= node_num; ++i) {
        if (container[i].is_visited == 0)
            dfs_visit(i, container);
    }

    for(int i = 1; i <= node_num; ++i) {
        printf("%d ", container[i].previous);
    }   printf("\n");

    sorted_list.print();
    

    // // bfs 부터 시작한다.
    // std::queue<Node*> queue;
    // for (int i = 0; i <= node_num; ++i) {
    //     container[i].is_visited = 0;
    //     container[i].previous = -1;
    // }

    // container[1].is_visited = 1;
    // container[1].distance = 0;
    // queue.push(&container[1]);
    // bfs_process(queue, container);

    // for(int i = 1; i <= node_num; ++i) {
    //     printf("%d ", container[i].previous);
    // }   printf("\n");
}
