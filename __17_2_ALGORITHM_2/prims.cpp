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
 * 프림 알고리즘은 Greedy algorithm 으로써, kruskal과 같이 반드시 최단 경로를 찾지는
 * 않는다. 방향성이 없는 각 노드간의 루프가 없는 undirected graph 의, 노드가 서로 연결되
 * 어 최소의 weight 으로 구성된 minimum spanning tree 을 만든다.
 * 이 알고리즘은, 한번에 한 노드씩 트리를 만들어서 트리로부터 아직 연결되지 않은 노드까지의
 * 최소한의 거리를 구해 더하는 식으로 구성된다.
 * Kruskal 은 가능한한 서로 연결되지 않은 그래프를 붙이는 식으로 최소신장트리를 구성하지만
 * Prim's 는 이미 만들어진 트리를 토대로 하나 하나씩 붙여나가는 형식으로 최소신장트리를
 * 구성한다.
 * 다른 소팅 알고리즘과는 비교시에 느리나, 만약 대상이 되는 그래프가 상당히 응집되어 있으면
 * 프림 알고리즘은 거의 O(n) 으로 작동할 수 있다. 다른 알고리즘과 섞어도 될듯...
 */ 

struct Vertex {
    int distance;
    int previous;

    Vertex() {
        distance = INFINITY;
        previous = -1;
    }
};

int main() {
    freopen(FILE_NAME, "r", stdin);

    int node_num, edge_num;
    scanf("%d %d", &node_num, &edge_num);



    // Print
    for (int i = 1; i <= node_num; ++i) {
        printf("%d : %d\n", i, node_set[i].distance);
    }

    return 0;
}