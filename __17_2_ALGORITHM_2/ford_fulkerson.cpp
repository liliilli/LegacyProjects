#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>

struct Node {
    int destination = -1; int capacity = 0; int flow = 0;
    Node* next_leaf = nullptr; Node* pair_addr = nullptr;
};

void print_nodes(Node* node, int size) {
    for (int i = 0; i < size; ++i) {
        Node* n = &node[i]; printf("S%d : %x : ", i, &node[i]);
        while (true) {
            auto dst = n->destination; auto cap = n->capacity;
            auto flow = n->flow; auto addr = n->pair_addr;

            printf("D%d,C%d,F%d, %x", dst, cap, flow, addr);
            if (n->next_leaf != nullptr) {
                n = n->next_leaf;
                if (n->destination != -1) { printf(" -> %x : ", n); }
                else { printf(" -> x "); break; }
            }
            else break;
        } printf("\n");
    }
}

void insert(Node* node, int dst, int cap) {
    // 이미 있는가 찾는다.
    if (node->destination == dst) { // if there is destination already
        if (node->capacity == 0) node->capacity = cap;
    }
    else { // If there is not destination
        if (node->next_leaf == nullptr) { // Cul de sak
            node->destination = dst; node->capacity = cap;
            node->next_leaf = new Node();
        }
        else {
            insert(node->next_leaf, dst, cap);
        }
    }
}

void find_pair_dst(Node* array, int src, int dst) {
    Node* src_item = &array[src];
    while (src_item != nullptr) {
        if (src_item->destination == dst)
            break;
        else
            src_item = src_item->next_leaf;
    }

    Node* dst_item = &array[dst];
    while (dst_item != nullptr) {
        if (dst_item->destination == src) {
            dst_item->pair_addr = src_item;
            src_item->pair_addr = dst_item;
            break;
        }
        else
            dst_item = dst_item->next_leaf;
    }
}

// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
// ford-folkerson method with edmonds-karp algorithm
// Flow are initialized to 0 whenever each edge is created.
// Weights are set, so we have to use priority_queue instead of general queue.
typedef const int cint; typedef int __id; typedef int __dis;
typedef std::vector<std::pair<int, Node*>> a_path;
typedef std::pair<__id, __dis> d_p;
struct dpOrder { // Need to implement Min priority heap
    bool operator()(d_p const& a, d_p const& b) const {
        return a.second > b.second;
} };
#define NOTHING -1

bool get_flag_bsp_exist(Node network[], cint start, cint end, a_path& path) {
    // Set
    std::vector<int> is_visited(end - start + 1), distance(end - start + 1);
    for (auto& dist : distance) dist = 999999;
    distance[start] = 0;

    std::priority_queue<d_p, std::vector<d_p>, dpOrder> queue;
    is_visited[start] = 1; queue.push(std::make_pair(start, 0));

    while (!queue.empty()) { // Start
        // Put it out.
        auto obj = queue.top(); queue.pop();
        cint src_id = obj.first; int dist = obj.second;
        Node* node  = &network[src_id];

        // Check each adjecent edge of source node.
        while (node->destination != NOTHING) {
            int dst     = node->destination;
            int res_cap = node->capacity - node->flow; // always get positive
            if (is_visited[dst] != 2 && 
                path[dst].first == NOTHING && dst != start && res_cap > 0) {
                is_visited[dst] = 1;

                if (dist + res_cap < distance[dst]) {
                    distance[dst] = dist + res_cap;
                    path[dst].first = src_id; path[dst].second = node;
                    printf("%d -> %d with %d\n", src_id, dst, distance[dst]);
                    queue.push(std::make_pair(dst, distance[dst]));
                }
            }
            node = node->next_leaf;
        }

        is_visited[src_id] = 2;
    }

    // Check
    if (path[end].first != NOTHING) return true;
    else                            return false;
}

int find_residual_cap(a_path& path, cint start, cint end) {
    int min     = 999999; int p_idx   = end;
    
    while (path[p_idx].first != -1) {
        Node* node          = path[p_idx].second;
        int residual_cap    = node->capacity - node->flow;

        if (min > residual_cap) min = residual_cap;

        printf("hoge : %d, prev : %d, residual cap : %d\n", p_idx, path[p_idx].first, residual_cap);
        printf("min : %d\n", min);
        p_idx = path[p_idx].first;
    }

    return min;
}

void reflect_flow(int res_cap, a_path& path) {
    int size = path.size();
    auto& pair = path[size - 1];
    while (pair.first != -1) {
        Node* node = pair.second;
        auto dst = node->destination; auto cap = node->capacity;
        auto flow = node->flow; auto addr = node->pair_addr;
        printf("S%d, D%d,C%d,F%d, %x\n", pair.first, dst, cap, flow, addr);

        int f = 0;
        do { // 간선에 있는 edge 만 뽑아서 넣는다.
            if (node->capacity == 0) node->flow -= res_cap; // If not network
            else node->flow += res_cap; // If in network

            node = node->pair_addr; f++;
        } while (f != 2);

        pair = path[pair.first];
    }
}

void process(Node network[], cint start, cint end) {
    // Initialization
    a_path augmented_path; augmented_path.resize(end - start + 1);
    for (auto& item : augmented_path) item.first = NOTHING;

    // Loop
    while (get_flag_bsp_exist(network, start, end, augmented_path)) {
        // Find min residual capacity
        auto min = find_residual_cap(augmented_path, start, end);
        reflect_flow(min, augmented_path);
        for (auto& item : augmented_path) item.first = NOTHING;
    }
}

int main() {
    freopen("ex0918_ford_input.txt", "r", stdin);

    // 생산자 소비자를 제외한 노드 수와 edge 수를 받는다.
    // 배열을 생성한다. 생성자 및 소비자 포함.
    int num_node = 0, num_edge = 0; scanf("%d %d", &num_node, &num_edge);
    printf("%d %d\n", num_node, num_edge);
    Node* flow_array = new Node[num_node + 2];

    // Input and make Network
    for (int i = 0; i < num_edge; ++i) {
        int src, dst, cap; scanf("%d %d %d", &src, &dst, &cap);

        insert(&flow_array[src], dst, cap); insert(&flow_array[dst], src, 0);
        find_pair_dst(flow_array, src, dst);
    }

    // Just print there are well.
    print_nodes(flow_array, num_node + 2);
    // Process to maximize flow.
    process(flow_array, 0, num_node + 2 - 1);
    puts(""); print_nodes(flow_array, num_node + 2); // Result

    return 0;
};