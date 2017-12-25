#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
using namespace std;
#pragma warning(disable:4996)

#define MIN(__A__, __B__) (__A__ > __B__) ? __B__ : __A__
#define ARR_SIZE(__A__) sizeof(__A__) / sizeof(__A__[0])
#define SWAP(__TYPE__, __A__, __B__) { \
        __TYPE__ temp = *__A__; *__A__ = *__B__; *__B__ = temp; \
    }

const int INF = 999999;
const std::string FILE_NAME = "input_olym.txt";

/**
 *
 */

struct LL_Node {
    unsigned id; LL_Node* prev; LL_Node* next;

    LL_Node(unsigned i) { id = i; next = prev = nullptr; }
};

struct LinkedList {
    LL_Node* first; LL_Node* end;
    LinkedList() { first = end = nullptr; }

    void insert(unsigned id) {
        LL_Node* node = new LL_Node(id);

        if (end != nullptr) {
            first->prev = node; node->next = first; first = node;
        }
        else { // 암것도 없다면
            first = end = node;
        }
    }

    void print() {
        if (end == nullptr) printf("No elements!\n");
        else {
            LL_Node* temp = first;
            while (temp != nullptr) {
                printf("%d ", temp->id); temp = temp->next;
            }   printf("\n");
        }
    }
};



/**
 *
 */

struct Edge {
    unsigned destination;
    int weight;
    Edge* next_edge;

    Edge(unsigned id, int weight) : destination(id), weight(weight), next_edge(nullptr) {};
};

struct Node {
    Edge*       first; Edge* end;
    int         is_visited;
    signed      distance; 
    unsigned    previous;

    Node() {
        first = nullptr; end = nullptr;
        is_visited = 0; distance = INF; previous = -1;
    }

    void insert(unsigned dst, int weight) {
        if (first == nullptr) { // 만약 컨테이너가 공백 상태라면
            first = new Edge(dst, weight);
            end = first;
        }
        else { // 이미 뭔가가 있다면
            Edge* temp = new Edge(dst, weight);
            end->next_edge = temp;
            end = temp;
        }
    }

    void print_elements() {
        if (first == nullptr) printf("No elements!\n");
        else {
            Edge* temp = first;
            while (temp != nullptr) {
                printf("%d, ", temp->destination); temp = temp->next_edge;
            }   printf("\n");
        }
    }
};

struct NodeInformation {
    unsigned area;
    int distance;
    unsigned weight;

    explicit NodeInformation(unsigned area, int distance, unsigned weight) :
        area(area), distance(distance), weight(weight) {};
};

// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** 

LinkedList sorted_list;
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

// Main 
int main() {
    std::ios_base::sync_with_stdio(false);
    freopen(FILE_NAME.c_str(), "r", stdin);

    unsigned node_number; cin >> node_number;
    unsigned end_index = node_number + 1;
    unsigned size = node_number + 2;
    Node* container = new Node[node_number + 2];

    // 맨 처음 (0)과 맨 마지막 (size() - 1)은 따로 초기화 해줘야함
    for (int dst_index = 1; dst_index <= node_number; ++dst_index)
        container[0].insert(dst_index, 0);

    // 값을 받는다.
    vector<NodeInformation> info_array;
    info_array.push_back(NodeInformation(0, 0, 0)); // Dummy
    for (int index = 1; index <= node_number; ++index) {
        unsigned area; int distance; unsigned weight;
        cin >> area >> distance >> weight; // input
        distance = -distance; // Inversion

        info_array.push_back(NodeInformation(area, distance, weight));
    }

    // 검증해서 Edge 을 만든다.
    for (int s = 1; s <= node_number; ++s) {
        for (int d = 1; d <= node_number; ++d) {
            if (s == d) continue; // 만약 자기 자신이랑 대조할려면 패스한다.

            auto& source = info_array[s];
            auto& desitnation = info_array[d];
            if (source.area >= desitnation.area && source.weight >= desitnation.weight)
                container[s].insert(d, source.distance);
        }

        // 마지막으로 중간 노드에 대해 끝점을 연결한다.
        container[s].insert(end_index, info_array[s].distance);
    }

    {
        // Print Test
        cout << "Linked List" << '\n';
        for (int i = 0; i < size; ++i) {
            container[i].print_elements();
        }
        cout << '\n';
    }

    // 됬네... 그러면 간단한 dfs 부터 시작한다.
    for (int i = 0; i <= size; ++i) {
        if (container[i].is_visited == 0) dfs_visit(i, container);
    }

    cout << "Topological Sort Result\n";
    sorted_list.print();
    cout << "\n";

    // Initialize Single Source
    container[0].distance = 0;

    // Sorting
    LL_Node* vertex = sorted_list.first;
    while (vertex != nullptr) {
        auto index = vertex->id;
        auto edge = container[index].first;
        while (edge != nullptr) {
            auto destination = edge->destination;

            if (container[index].distance + edge->weight < container[destination].distance) {
                container[destination].distance = container[index].distance + edge->weight;
                container[destination].previous = index;
            }
            
            // 갈아 끼운다.
            edge = edge->next_edge;
        }

        vertex = vertex->next;
    }

    // Print
    auto count = 0;
    auto i = container[size - 1].previous;
    while (i != 0) {
        ++count;
        i = container[i].previous;
    }


    cout << count << '\n';
    i = container[size - 1].previous;
    while (i != 0) {
        cout << i << '\n';
        i = container[i].previous;
    }
    cout << "Weight : " << -container[size - 1].distance << '\n';

    return 0;
}