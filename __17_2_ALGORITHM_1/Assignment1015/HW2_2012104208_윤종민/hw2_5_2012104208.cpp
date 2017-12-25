#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, qsort
#include <string.h>
#include <ctype.h>
#include <math.h>
#define min(__A__, __B__) (__A__ > __B__) ? __B__ : __A__
#define FILE_PATH "kakao05_input.txt"
struct Node { char element[3]; unsigned count = 1; };
struct Pair { unsigned size = 0; unsigned count = 0; };

int compare(const void *a, const void *b) { 
    return strcmp(((Node*)a)->element, ((Node*)b)->element); 
}

int is_exist(Node arr[], char* src, unsigned size) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(arr[i].element, src) == 0) return i;
    }
    return -1;
}

Pair make_array(Node arr[], char src[]) {
    int i = 0, j = 0; char left = 0, right = 0; Pair pair;

    while (src[i] != NULL) {
        right = src[i];
        if (isalpha(left) && isalpha(right)) {
            right = islower(right) ? toupper(right) : right; // 대문자화
            char temp[3]; temp[0] = left; temp[1] = right; // 임시 버퍼
            
            int res = is_exist(arr, temp, j);
            if (res == -1) { // 만약 중복이 없으면
                Node node; strcpy(node.element, temp); // 노드를 만들어서 배열에 넣음.
                arr[j] = node; ++j; ++pair.count;
            } else { 
                ++pair.count; arr[res].count += 1;
            } // 중복이 있으면
        } else if (isalpha(right))
            right = islower(right) ? toupper(right) : right;

        left = right; ++i;
    }

    pair.size = j;
    return pair;
}

unsigned get_intersection(Node arr[], unsigned size) {
    Node* prev = NULL; unsigned intersection_size = 0;

    for (int i = 0; i < size; ++i) { // 대조군들이 같으면 최소값을 증가
        if (prev != NULL && strcmp(prev->element, arr[i].element) == 0) { 
            intersection_size += min(prev->count, arr[i].count);
        }
        prev = &arr[i];
    }

    return intersection_size;
}

int main(int argc, char* argv[]) {
    freopen(argv[1], "r", stdin);
    char left[1001], right[1001]; // 입력 버퍼 + '\0'
    scanf("%[^\n]s", left); 
    getc(stdin); fgets(right, sizeof(right), stdin);

    // 원소 배열을 만든다.
    Node* n_left    = (Node*)malloc(sizeof(Node) * 1000);  
    Node* n_right   = (Node*)malloc(sizeof(Node) * 1000);
    Pair  lp    = make_array(n_left, left);
    Pair  rp    = make_array(n_right, right);

    if (lp.size == 0 && rp.size == 0) { // l_size 와 r_size 가 0 일 때.
        free(n_left); free(n_right); printf("%d\n", 65536);
    } 
    else { // 만약 배열이 있으면 합치고, 정렬한다.
        Node* n_array = (Node*)malloc(sizeof(Node) * (lp.size + rp.size));
        int j = 0;
        for (int i = 0; i < lp.size; ++i) { n_array[j++] = n_left[i]; } 
        for (int i = 0; i < rp.size; ++i) { n_array[j++] = n_right[i]; } 
        free(n_left); free(n_right);
        qsort(n_array, lp.size + rp.size, sizeof(Node), compare);
        
        float itsect_sz  = (float)get_intersection(n_array, lp.size + rp.size);
        float union_sz   = (float)(lp.count + rp.count) - itsect_sz;
        free(n_array); 
        printf("%.0f\n", floor(itsect_sz / union_sz * 65536));
    }
}

