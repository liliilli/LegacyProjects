#include <iostream>
#define MINE -1

class Sets {
public:
    Sets(int sz);
    
    void weighted_union(int i, int j);
    int collapsing_find(int i);
    void print() {
        for (int i = 0; i <= number; ++i) {
            printf("%d : %d\t", i, parent[i]);
        }
        printf("\n");
    }
private:
    int* parent;
    int number;
};

Sets::Sets(int sz) {
    number = sz;
    parent = new int[sz + 1];
    for (int i = 0; i <= number; ++i)
        parent[i] = MINE;
}

void Sets::weighted_union(int i, int j) {
    int temp = parent[i] + parent[j];
    printf("%d\n", temp);
    if ( parent[i] > parent[j] ) {
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }
}

int Sets::collapsing_find(int i) {
    int r = i;
    for (;parent[r] >= 0; r = parent[r]); // find root

    // 따라서 input i 와 찾은 최종 루트 r 이 서로 같지 않으면,
    // 즉, 자기 자신 혼자인 트리가 아닌 것을 알게 되면
    while (i != r) {
        int s = parent[i]; // parent[i] 의 부모값을 임시로 저장.
        parent[i] = r; // 최종 루트로 바꿔친다.
        i = s; // i 의 부모값으로 다시 루프를 돌릴 수 있도록 갱신.
    }

    return r; // 최종 루트노드의 값을 반환한다.
}

void kruskal(int, Sets*);

FILE* stream = fopen("ex0901_input_1.txt", "r");

int main() {
    int node_size, edge_size;

    fscanf(stream, "%d %d\n", &node_size, &edge_size);
    Sets* edge_list = new Sets(node_size);

    kruskal(edge_size, edge_list);
    
    fclose(stream);
    delete edge_list;
    return 0;
}

void kruskal(int edge_size, Sets* edge_list) {
    int root, child, weight;
    for (int i = 0; i < edge_size - 1; ++i) {
        fscanf(stream, "%d %d %d\n", &root, &child, &weight);
        int root_left = edge_list->collapsing_find(root);
        int root_right = edge_list->collapsing_find(child);

        // 루트가 다르기 때문에 붙여줘야 한다.
        if (root_left != root_right) {
            edge_list->weighted_union(root_left, root_right);
            printf("%d %d %d\n", root, child, weight);
        }
        edge_list->print();
    }
}
