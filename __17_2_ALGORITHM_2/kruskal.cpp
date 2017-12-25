#include <iostream>
#define MINE -1 // 자기 것

// 최소 신장 트리를 만들어서 greedy 하지만 shortest path 을 찾는다.
class Sets {
public:
    Sets(int sz);

    void weighted_union(int i, int j);
    int collapsing_find(int i);

private:
    std::vector<int> of_parent; // 노드에 연결 된 가장 최상위의 root 을 가리킨다.
    // 만약 자기 자신이 root 라면, 마이너스 형태로 node 수를 기록한다.
};

Sets::Sets(int init_size) {
    // parent 는 chid -> parent 가 되는 배열로 값으로 연결될 노드 위치를 가리킨다.
    of_parent = std::vector<int>(of_parent + 1); // 생성
    // 아직 모든 노드가 다 떨어진 상태라고 본다.
    for (int i = 0; i <= init_size; ++i) of_parent[i] = MINE; // 아직 연결 X됨.
}

void Sets::weighted_union(int i, int j) {
    int temp = parent[i] + parent[j]; // 서브 트리를 붙여야 하기 때문에 먼저 노드 수를 합친다.

    if ( parent[i] > parent[j] ) { // 노드수를 비교한다.
        parent[i] = j; // 만약, i 쪽이 j 쪽보다 노드 수가 작으면 j 쪽에 붙인다.
        parent[j] = temp; // 이 떄 루트의 노드 수는 마이너스로 반전되서 저장된다.
    } else {
        parent[j] = i; // 만약, j 쪽이 i 쪽보다 노드 수가 작으면 i 쪽에 붙인다.
        parent[i] = temp; // 이 떄 루트의 노드 수는 마이너스로 반전되서 저장된다.
    }
}

int Sets::collapsing_find(int i) {
    int r = i; // Knapsack 문제를 볼 것 (알고리즘 1 중간 시험)
    for (;parent[r] >= 0; r = parent[r]); // 지금 노드에 연결된 서브 트리의 루트를 찾는다.

    // 따라서 input i 와 찾은 최종 루트 r 이 서로 같지 않으면,
    // 즉, 자기 자신 혼자인 트리가 아닌 것을 알게 되면
    while (i != r) {
        int s = parent[i]; // parent[i] 의 부모값을 임시로 저장.
        parent[i] = r; // 최종 루트로 바꿔친다.
        i = s; // i 의 부모값으로 다시 루프를 돌릴 수 있도록 갱신.
    }

    return r; // 서브트리의 최종 루트 노드의 값을 반환한다.
}

void kruskal(int edge_size, Sets* edge_list) {
    int src, dst, weight;
    for (int i = 0; i < edge_size - 1; ++i) { // MST를 여기 저기서 만드므로 큐 없어도 상관 X
        std::cin >> src >> dst >> weight;
        int root_src = edge_list->collapsing_find(src);
        int root_dst = edge_list->collapsing_find(dst);

        // 루트가 다르기 때문에 붙여줘야 한다.
        if (root_src != root_dst) {
            edge_list->weighted_union(root_src, root_dst);
            // 출력
            printf("%d %d %d\n", src, dst, weight);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("ex0901_input_1.txt", "r", stdin);

    // 입력
    int node_size, edge_size; std::cin >> node_size >> edge_size;
    // 처리
    Sets* edge_list = new Sets(node_size);
    kruskal(edge_size, edge_list);
    delete edge_list;

    return 0;
}