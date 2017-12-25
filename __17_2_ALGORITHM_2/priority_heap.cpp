#include <iostream>
#include <iomanip>
#include <vector>
// #pragma warning(disable:4996)
#define PRINT_HEAP(_L, _STR) \
    for (auto val : _L) { if (val != -1) \
        std::cout << std::setw(2) << val << " "; \
    } \
    std::cout << _STR; 

using Node = int;
using Array = std::vector<Node>;

int size = 0;

void heapify(Array& heap_arr, const unsigned index) {
    auto result_index = index;
    auto left_i = 2 * index;
    auto right_i = left_i + 1;

    // Processing
    if (left_i <= size && heap_arr[result_index] >= heap_arr[left_i]) {
        result_index = left_i;
    }
    if (right_i <= size && heap_arr[result_index] >= heap_arr[right_i]) {
        result_index = right_i;
    }

    // Checking
    if (result_index != index) {
        std::swap(heap_arr[result_index], heap_arr[index]);
        heapify(heap_arr, result_index);
    }
}

void makeHeap(Array& heap_array) {
    auto start = size / 2;
    for (int i = start; i >= 1; --i) { heapify(heap_array, i); }
}

Node returnRoot(Array& heap_array) {
    Node temp = heap_array[1];

    std::swap(heap_array[1], heap_array[size]);
    size -= 1;
    heapify(heap_array, 1);

    return temp;
}

void heapRemoveKeys(Array& heap_array, Array& res_arr) {
    int result_size = size;
    for (int index = size; index >= 1; --index) {
        res_arr[result_size - index + 1] = returnRoot(heap_array);
    }

    size = heap_array.size() - 1;
}

void heapSort(Array& source, Array& destination) {
    makeHeap(source);
    heapRemoveKeys(source, destination);
}

void heapInsert(Array& heap_array, const Node value) {
    heap_array.push_back(value);
    int index = size + 1;

    int parent = index / 2;
    for (; parent >= 1;) {
        if (heap_array[parent] > heap_array[index]) {
            std::swap(heap_array[parent], heap_array[index]);
            index = parent; parent = index / 2;
        }
        else break;
    }

    size++;
}

void heapRemove(Array& heap_array) {
    std::swap(heap_array[1], heap_array[size]); 
    heap_array.pop_back();

    --size;
    makeHeap(heap_array);
}

template<typename T> T input() { T value; std::cin >> value; return value; }

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("input_heap.txt", "r", stdin);

    // Initiation
    std::cin >> size;
    Array heap_array(size + 1, -1); 

    // Input
    for (decltype(size) i = 1; i <= size; ++i) { heap_array[i] = input<int>(); }
    PRINT_HEAP(heap_array, "Input Array\n");

    // Make Heap!
    makeHeap(heap_array);           PRINT_HEAP(heap_array, "Make Heap\n");

    // Heap Sort!
    Array* heap2 = new Array(heap_array);

    Array result = Array(heap_array.size(), -1); 
    heapSort(heap_array, result);   PRINT_HEAP(result, "Heap Sorted inorder\n");

    heap_array = *heap2; delete heap2;

    // Command
    heapInsert(heap_array, 50);     PRINT_HEAP(heap_array, "Insert 50\n");
    heapRemove(heap_array);         PRINT_HEAP(heap_array, "Remove min\n");
    heapInsert(heap_array, 11);     PRINT_HEAP(heap_array, "Insert 11\n");
    heapInsert(heap_array, 1);      PRINT_HEAP(heap_array, "Insert 1\n");
    heapRemove(heap_array);         PRINT_HEAP(heap_array, "Remove min\n");

    return 0;
}