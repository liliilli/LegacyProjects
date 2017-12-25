#include <iostream>
#include <vector>
#include <utility>

#define MIN(__A__, __B__) (__A__ > __B__) ? __B__ : __A__
#define ARR_SIZE(__A__) sizeof(__A__) / sizeof(__A__[0])
#define SWAP(__TYPE__, __A__, __B__) { \
        __TYPE__ temp = *__A__; *__A__ = *__B__; *__B__ = temp; \
    }

#define FILE_NAME "ex0901_input.txt"
#define INFINITY 9999999

using neighbor_info = std::pair<unsigned, int>;
struct Vertex {
    int distance;
    bool is_visited;

    int previous;
    std::vector<neighbor_info> neighbors;

    Vertex() {
        distance = INFINITY;
        is_visited = false;
        previous = -1;
    }

    void insert_information(unsigned int destination, int distance) {
        neighbors.push_back(std::make_pair(destination, distance));
    }
};

unsigned get_shortest_distance(std::vector<Vertex>& node_set) {
    unsigned shortest_index = 0;
    int distance = INFINITY;

    for (int i = 1; i <= node_set.size(); ++i) {
        if (!node_set[i].is_visited && node_set[i].distance < distance) {
            shortest_index = i;
            distance = node_set[i].distance;
        }
    }

    return shortest_index;
};

void print_path_of(std::vector<Vertex>& set, unsigned i) {
    int target = i;
    printf("%d -> ");
    while (set[target].previous != -1) {
        target = set[target].previous;
        printf("%d -> ", target);
    }   
    printf("\n");
}

void init_node_set(std::vector<Vertex>& node_set, int edge_num) {
    for (int i = 0; i < edge_num; ++i) {
        int src, dst, distance;
        scanf("%d %d %d", &src, &dst, &distance);
        node_set[src].insert_information(dst, distance);
    }
}

void find_shortest_path(std::vector<Vectex>& node_set) {
    // 경로를 찾게 한다. 이 때 걸리는 시간은 O(n2).
    for (int i = 1; i <= node_num; ++i) {
        // 우선 현재 방문하지 않은 노드 중에서 가장 작은 잠정적인 distance 를
        // 가진 노드를 고른다. 그리고 다음 루프에서 이 노드를 체크하지 않도록
        // 마크한다.
        unsigned src_index = get_shortest_distance(node_set);
        node_set[src_index].is_visited = true;

        // 그 노드와 인접한 이웃들을 찾아서 현재 가지고 있는 거리 값과
        // 갱신될 거리 값을 비교해서 가장 작은 것을 갱신한다. 
        for (auto& node : node_set[src_index].neighbors) {
            int alt = node_set[src_index].distance + node.second;

            if (alt < node_set[node.first].distance) {
                node_set[node.first].distance = alt;
                node_set[node.first].previous = src_index;
            }
        }
    }
}

int main() {
    freopen(FILE_NAME, "r", stdin);

    // node 의 수와 edge 의 수를 받는다.
    // 이 때 node 는 전부, 방문되지 않은 상태로 두며, node 안에 목적지와 간선의 가중치를 가진
    // 정보를 배열로 때려넣는다.

    // 그 후에, 시작 지점에서 아직 방문하지 않은 인접한 모든 노드에 대해,
    // 현재 주어진 거리와 현재 거리에서 간선 가중치를 더한 거리를 비교해서 최소인 거리를 갱신하도록 한다.
    // 그 후에, 방문된 노드에서 인접한 노드의 번호를 받아 큐르 돌려 나가면서 차례차례 방문을 하도록 한다.
    // O(n^2) , O(n^2) 의 시간 및 공간 복잡도를 가진다.
    int node_num, edge_num; scanf("%d %d", &node_num, &edge_num);

    std::vector<Vertex> node_set(size + 1);
    node_set[1].distance = 0;
    init_node_set(node_set, edge_num);

    find_shortest_path(node_set);

    // Print
    for (int i = 1; i <= node_num; ++i) {
        printf("%d : %d\n", i, node_set[i].distance);
        print_path_of(node_set, i);
    }

    return 0;
}