#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FILE_PATH "kakao03_input.txt"

unsigned int used_time = 0;

struct Node {
    char name[21]; // 최대 20자로 이루어져 있다. 이름은 다 대문자로 저장.
    Node* more_new = NULL; // 꼬리에 붙은 비교적 최신 노드를 가리킴
    Node* more_old = NULL; // 앞에 붙은 비교적 낡은 노드를 가리킴
};

struct Queue {
    unsigned max = 0; // 담을 수 있는 한계 사이즈
    unsigned size = 0; // 지금 담은 사이즈
    Node* start = NULL; // 가장 오래된 노드를 가리킴
    Node* end = NULL; // 최근에 쓰였거나 한 노드를 가리킴.
};

void insert_queue(Queue* queue, Node* node) {
    if (queue->start == NULL) { // 만약 Queue 가 초기상태라면
        queue->start = node; queue->end = node; // start, end 둘다 node 주소로 향함.
        queue->size++;
    } else { // 이미 존재하면 최신(end) 뒤(더 최신)에 node 을 붙인다.
        // 이 떄 사이즈가 max 일 경우에는..
        if (queue->size >= queue->max) {
            Node* del_obj = queue->start; // 지울 객체 (가장 안씀)를 미리 옮겨준다.
            queue->start = queue->start->more_new; // 앞으로 땡겨준다.
            queue->start->more_old = NULL; // 가장 앞으로 온 객체의 old 을 NULL 로

            queue->end->more_new = node; // 가장 끝 객체의 new 을 node (가장 최신)로
            node->more_old = queue->end; // 가장 최신의 old 을 이전 객체로
            queue->end = node; // queue 의 가장 최신을 node 로 향하게 한다.
            node->more_new = NULL;

            free(del_obj); // 가장 안쓴 객체를 지운다.
        } else { // size 가 max 보다 작을 경우에는
            node->more_old = queue->end; 
            queue->end->more_new = node;
            queue->end = node;
            queue->size++;
        }
    }
}

void to_upper(char name[]) {
    int i = 0;
    while (1) {
        if (islower(name[i])) { name[i] = toupper(name[i]); }
        else if (name[i] == 0) break;
        
        ++i;
    }
};

bool find_cache(Queue* queue, char name[]) {
    // queue 의 start 부터 end 까지 쭈욱 뒤져본다.
    Node* temp = queue->start;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) { // 만약 캐시를 찾았으면
            if (temp->more_old == NULL) { // 캐시 노드 위치가 맨 처음이면 맨 뒤로 보냄
                queue->start = temp->more_new;
                queue->start->more_old = NULL;

                temp->more_old = queue->end;
                temp->more_new = NULL;
                queue->end->more_new = temp;
                queue->end = temp;
            }
            else if (temp->more_new != NULL) { // 캐시 노드 위치가 마지막이 아니면
                temp->more_old->more_new = temp->more_new;
                temp->more_old = queue->end;
                temp->more_new = NULL; 
            } // 마지막이면 그대로 둔다.

            return true; // 플래그 true 을 반환한다.
        } 
        else { // 캐시를 몾 찾았을 경우에는 뒤의 것을 돌린다.
            temp = temp->more_new;
        }
    }

    return false; // 캐시를 몾 찾았을 경우에는 false을 반환한다.
}

int main(int argc, char* argv[]) {
    freopen(argv[1], "r", stdin);

    Queue queue; // 우선 큐를 만든다.
    // 입력
    unsigned city_num;
    scanf("%d %d", &queue.max, &city_num);

    for (int i = 0; i < city_num; ++i) {
        char name[21]; scanf("%s", name); // 도시 이름을 받는다.
        to_upper(name); // 대문자로 바꾼다.

        // 여기서, 캐시 작업을 처리한다.
        if (find_cache(&queue, name)) { // True 이면 Hit 이다.
            used_time += 1;
        } else { // False 이면 Miss 이다.
            used_time += 5;
            
            if (queue.max != 0) {
                Node* node = (Node*)malloc(sizeof(Node)); // 노드를 만든다.
                strcpy(node->name, name); // 복사한다.
                insert_queue(&queue, node); // 만약 같은게 없으면 삽입한다.
            }
        }
    }

    printf("%d\n", used_time);
    return 0;
}