#include <iostream>
#define MINE -1

struct Sets {
    Sets(int );
    
    void weighted_union(int dead, int job);
    int collapsing_find(int);

    int get_root(int i) { return root[i]; }
    int get_dead(int i) { return deadline[i]; };

    int* deadline; // Deadline 을 가리킴
    int* job;
    int* root;   // root 을 가리킴
    int number;
};

Sets::Sets(int size) {
    number = size;
    deadline = new int[size + 1];
    
    root = new int[size + 1];
    root[0] = size;
    for (int i = 1; i <= size; ++i)
        root[i] = MINE;
    for (int i = 1; i <= size; ++i)
        deadline[i] = i;

    job = new int[size + 1];
}

void Sets::weighted_union(int i, int j) {
    int temp = root[i] + root[j];
    // printf("temp : %d\n", temp);
    if ( root[i] > root[j] ) {
        root[i] = j;
        root[j] = temp;
        deadline[j] = deadline[i];
    } else {
        root[i] = temp; // 위치 지정
        root[j] = i; // 루트로서의 총 노드 수 
    }
}

int Sets::collapsing_find(int i) {
    int r = i;
    for (;root[r] >= 0; r = root[r]); // find root

    // 따라서 input i 와 찾은 최종 루트 r 이 서로 같지 않으면,
    // 즉, 자기 자신 혼자인 트리가 아닌 것을 알게 되면
    while (i != r) {
        int s = root[i]; // parent[i] 의 부모값을 임시로 저장.
        root[i] = r; // 최종 루트로 바꿔친다.
        i = s; // i 의 부모값으로 다시 루프를 돌릴 수 있도록 갱신.
    }

    return r; // 최종 루트노드의 값을 반환한다.
}

void job_scheduling(int , Sets* );

int main() {
    freopen("scheduling_input.txt", "r", stdin);
    // freopen("ex0911_scheduling.txt", "r", stdin);
    int size;

    scanf("%d\n", &size);
    Sets* edge_list = new Sets(size);

    job_scheduling(size, edge_list);

    delete edge_list;
    return 0;
}

void job_scheduling(int size, Sets* list) {
    int job, deadline, profit;
    for (int i = 0; i < size; ++i) {
        scanf("%d %d %d\n", &job, &deadline, &profit);
        int root = list->collapsing_find(deadline);
        list->job[list->deadline[root]] = job;
        int root_pre = list->collapsing_find(list->get_dead(root) - 1);

        printf("Root:%d, Root_pre:%d\n", root, root_pre);
    
        list->weighted_union(root_pre, root);

        for (int i = 1; i <= size; ++i) {
            printf("%d ", list->root[i]);
        } printf("\n");
        for (int i = 1; i <= size; ++i) {
            printf("%d ", list->job[i]);
        } printf("\n");
        for (int i = 1; i <= size; ++i) {
            printf("%d ", list->deadline[i]);
        } printf("\n");
    }
}
