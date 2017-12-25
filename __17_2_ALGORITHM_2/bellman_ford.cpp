#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

#define MIN(__A__, __B__) (__A__ > __B__) ? __B__ : __A__
#define ARR_SIZE(__A__) sizeof(__A__) / sizeof(__A__[0])
#define SWAP(__TYPE__, __A__, __B__) { \
        __TYPE__ temp = *__A__; *__A__ = *__B__; *__B__ = temp; \
    }

#define FILE_NAME "ex0901_input.txt"
#define INFINITY 9999999

/**
 * 벨만포드 알고리즘은, weighted digraph 에서 어느 한 vertex 로부터 다른 vertex 까지의
 * 최소 거리를 구하는 알고리즘이다. Dijkstra 알고리즘보다는 약간 느리지만, 좀 더 여러 방면
 * 에서 쓰일 수 있으며, weight 가 negative 인 경우에 대해서도 최소 경로를 구할 수 있다.
 */ 

struct Vertex {
    int distance; int previous;

    Vertex() { distance = INFINITY; previous = -1; }
};

int main() {
    freopen(FILE_NAME, "r", stdin);

    int node_num, edge_num; scanf("%d %d", &node_num, &edge_num);

    // 초기화
    std::vector<Vertex> node_set(node_num + 1);
    // 첫번째 인자는 src 이며, 두번째는 dst 이고, 세번째는 이 두 노드 사이의 거리이다.
    std::vector<std::tuple<unsigned, unsigned, int>> edge_set(edge_num);
    for (int i = 0; i < edge_num; ++i) {
        unsigned s, e; int distance;
        scanf("%d %d %d", &s, &e, &distance);
        edge_set.push_back(std::make_tuple(s, e, distance));
    }
    node_set[1].distance = 0;

    // 정렬한다. (relax the distance)
    // 이 과정으로 인해 O(n^2) 가 발생된다.
    for (int i = 1; i < node_set.size(); ++i) {
        for (auto& edge : edge_set) {
            auto s = std::get<0>(edge); auto e = std::get<1>(edge);
            auto w = std::get<2>(edge);

            // Relax
            if (node_set[s].distance + w < node_set[e].distance) {
                node_set[e].distance = node_set[s].distance + w;
                node_set[e].previous = s;
            }
        }
    }

    // Negative Distance 가 있는가 체크한다.
    // O(n)
    for (auto& edge : edge_set) {
        auto s = std::get<0>(edge); auto e = std::get<1>(edge);
        auto w = std::get<2>(edge);

        if (node_set[s].distance + w < node_set[e].distance) {
            fprintf(stderr, "Graph contains negative-weight cycle");
        }
    }

    // Print
    for (int i = 1; i <= node_num; ++i) {
        printf("%d : %d\n", i, node_set[i].distance);
    }

    return 0;
}