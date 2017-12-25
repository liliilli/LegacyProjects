#include <iostream>
#include <iomanip>
#include <vector>
#pragma warning(disable:4996)

using node_id = int;
using dist = int;

struct HeapNode {
    node_id index; dist distance;
    HeapNode() {};
    HeapNode(node_id id, dist distance) : index(id), distance(distance) {};
};
using HeapArray = std::vector<HeapNode>;

unsigned size = 0;
void heapify(HeapArray& heap_arr, const unsigned index) {
    auto result_index = index;
    auto left_i = 2 * index;
    auto right_i = left_i + 1;

    // Processing
    if (left_i <= size && 
        heap_arr[result_index].distance >= heap_arr[left_i].distance) {
        result_index = left_i;
    }
    if (right_i <= size && 
        heap_arr[result_index].distance >= heap_arr[right_i].distance) {
        result_index = right_i;
    }

    // Checking
    if (result_index != index) {
        std::swap(heap_arr[result_index], heap_arr[index]);
        heapify(heap_arr, result_index);
    }
}

void makeHeap(HeapArray& heap_array) {
    auto start = size / 2;
    for (int i = start; i >= 1; --i) { heapify(heap_array, i); }
}

HeapNode returnRoot(HeapArray& heap_array) {
    HeapNode temp = heap_array[1];

    std::swap(heap_array[1], heap_array[size]);
    size -= 1;
    heapify(heap_array, 1);

    heap_array.pop_back();
    return temp;
}

void heapRemoveKeys(HeapArray& heap_array, HeapArray& res_arr) {
    int result_size = size;
    for (int index = size; index >= 1; --index) {
        res_arr[result_size - index + 1] = returnRoot(heap_array);
    }

    size = heap_array.size() - 1;
}

void heapSort(HeapArray& source, HeapArray& destination) {
    makeHeap(source);
    heapRemoveKeys(source, destination);
}

void heapInsert(HeapArray& heap_array, const HeapNode value) {
    heap_array.push_back(value);
    int index = size + 1;

    int parent = index / 2;
    for (; parent >= 1;) {
        if (heap_array[parent].distance > heap_array[index].distance) {
            std::swap(heap_array[parent], heap_array[index]);
            index = parent; parent = index / 2;
        }
        else break;
    }
    size++;
}

void heapRemove(HeapArray& heap_array) {
    std::swap(heap_array[1], heap_array[size]);
    heap_array.pop_back();

    --size;
    makeHeap(heap_array);
}

/**
 * Input Helper Method
 */
template<typename T> 
T input() { T value; std::cin >> value; return value; }

/**
 * Heap Test Function
 */

//void heap_test() {
//    freopen("input_heap.txt", "r", stdin);
//
//    // 1. Initiation
//    std::cin >> size;
//    Array heap_array(size + 1, -1);
//
//    // 2. Input
//    for (decltype(size) i = 1; i <= size; ++i) { heap_array[i] = input<int>(); }
//    PRINT_HEAP(heap_array, "Input Array\n");
//
//    // 3. Make Heap!
//    makeHeap(heap_array);           PRINT_HEAP(heap_array, "Make Heap\n");
//
//    // 4. Heap Sort!
//    Array* heap2 = new Array(heap_array);
//
//    Array result = Array(heap_array.size(), -1);
//    heapSort(heap_array, result);   PRINT_HEAP(result, "Heap Sorted inorder\n");
//
//    heap_array = *heap2; delete heap2;
//
//    // 5. Command
//    heapInsert(heap_array, 50);     PRINT_HEAP(heap_array, "Insert 50\n");
//    heapRemove(heap_array);         PRINT_HEAP(heap_array, "Remove min\n");
//    heapInsert(heap_array, 11);     PRINT_HEAP(heap_array, "Insert 11\n");
//    heapInsert(heap_array, 1);      PRINT_HEAP(heap_array, "Insert 1\n");
//    heapRemove(heap_array);         PRINT_HEAP(heap_array, "Remove min\n");
//}

/**
 * Prim MST Test Function
 */

struct PrimEdge {
    node_id     destination;
    dist        edge_distance;

    PrimEdge*   next = nullptr;

    PrimEdge(node_id destination, dist distance)
        : destination(destination), edge_distance(distance) {};
};

struct PrimNode {
    using flg = int;

    node_id     id;
    dist        distance = 9999999;
    flg         flag = 0;

    PrimEdge*   edge = nullptr;
    node_id     parent = -1;

    PrimNode(node_id id = -1) : id(id) {};

    void insertEdge(PrimEdge* insert_edge) {
        auto temp_edge = &edge;
        while (*temp_edge != nullptr) { temp_edge = &(*temp_edge)->next; }

        (*temp_edge) = insert_edge;
    }

    void printAll() {
        auto temp_edge = &edge;
        while (*temp_edge != nullptr) { 
            std::cout << (*temp_edge)->destination << " ";
            temp_edge = &(*temp_edge)->next; 
        }
    }

    HeapNode makeHeapNode() { return HeapNode(id, distance); }
};

void prim_test() {
    freopen("input_prim.txt", "r", stdin);

    // 1. Initiation
    int node_number, edge_number;
    std::cin >> node_number >> edge_number;

    // 1-1. Make Node Container
    std::vector<PrimNode> node_array(node_number + 1); // 0 is not used.
    for (int i = 1; i <= node_number; ++i) { node_array[i].id = i; }

    // 1-2. Input nodes and edges
    for (int i = 0; i < edge_number; ++i) {
        int node_source, node_destination, edge_distance;
        std::cin >> node_source >> node_destination >> edge_distance;

        // Make Edge to Node
        PrimEdge* edge = new PrimEdge(node_destination, edge_distance);
        node_array[node_source].insertEdge(edge);
    }

    // 1-3. Print Test
    for (auto& node : node_array) {
        std::cout << node.id << std::endl;
        node.printAll();
        std::cout << std::endl;
    }

    // 2. Proceed Prim
    std::vector<HeapNode> heap_array(1);

    node_array[1].distance = 0;
    heapInsert(heap_array, node_array[1].makeHeapNode());

    while (heap_array.size() != 1) { // while PQ != Empty Set
        auto u = returnRoot(heap_array);

#ifdef _DEBUG
        std::cout << u.index << " " << u.distance << std::endl;
#endif
        // 각 인접한 노드를 찾는다.
        auto temp_edge = node_array[u.index].edge;
        while (temp_edge != nullptr) {
            auto v = temp_edge->destination;
            auto weight = temp_edge->edge_distance;

            // 거리 측정 및 플래그 측정
            if (node_array[v].flag == 0 && weight < node_array[v].distance) {
                node_array[v].parent = u.index;
                node_array[v].distance = weight;
                
                heapInsert(heap_array, node_array[v].makeHeapNode());
            }

            temp_edge = temp_edge->next;
        }

        node_array[u.index].flag = 1;
    }

    // Print Result
    int sum = 0;
    for (int i = 1; i <= node_number; ++i) {
        std::cout << node_array[i].parent << " ";
        sum += node_array[i].distance;
    } 
    std::cout << std::endl;
    std::cout << "weight 합 : " << sum << std::endl;
    for (int i = 1; i <= node_number; ++i) {
        std::cout << node_array[i].distance << " ";
    }
    std::cout << std::endl;
}

void dijkstra_test() {
    freopen("input_dijkstra.txt", "r", stdin);

    // 1. Initiation
    int node_number, edge_number;
    std::cin >> node_number >> edge_number;

    // 1-1. Make Node Container
    std::vector<PrimNode> node_array(node_number + 1); // 0 is not used.
    for (int i = 1; i <= node_number; ++i) { node_array[i].id = i; }

    // 1-2. Input nodes and edges
    for (int i = 0; i < edge_number; ++i) {
        int node_source, node_destination, edge_distance;
        std::cin >> node_source >> node_destination >> edge_distance;

        // Make Edge to Node
        PrimEdge* edge = new PrimEdge(node_destination, edge_distance);
        node_array[node_source].insertEdge(edge);
    }

    // 1-3. Print Test
    for (auto& node : node_array) {
        std::cout << node.id << std::endl;
        node.printAll();
        std::cout << std::endl;
    }

    // 2. Proceed Prim
    std::vector<HeapNode> heap_array(1);

    node_array[1].distance = 0;
    heapInsert(heap_array, node_array[1].makeHeapNode());

    while (heap_array.size() != 1) { // while PQ != Empty Set
        auto u = returnRoot(heap_array);

#ifdef _DEBUG
        std::cout << u.index << " " << u.distance << std::endl;
#endif
        // 각 인접한 노드를 찾는다.
        auto temp_edge = node_array[u.index].edge;
        while (temp_edge != nullptr) {
            auto v = temp_edge->destination;
            auto weight = node_array[u.index].distance + temp_edge->edge_distance;

            // 거리 측정 및 플래그 측정
            if (node_array[v].flag == 0 && weight < node_array[v].distance) {
                node_array[v].parent = u.index;
                node_array[v].distance = weight;
                
                heapInsert(heap_array, node_array[v].makeHeapNode());
            }

            temp_edge = temp_edge->next;
        }

        node_array[u.index].flag = 1;
    }

    // Print Result
    int sum = 0;
    for (int i = 1; i <= node_number; ++i) {
        std::cout << node_array[i].parent << " ";
        sum += node_array[i].distance;
    } 
    std::cout << std::endl;
    std::cout << "weight 합 : " << sum << std::endl;
    for (int i = 1; i <= node_number; ++i) {
        std::cout << node_array[i].distance << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);

    dijkstra_test();
    return 0;
}