#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, qsort

int compare(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

int main(int argc, char* argv[]) {
    freopen(argv[1], "r", stdin);

    // 입력
    int bus_num;    // 버스 운행 횟수 (대수)
    int bus_term;   // 버스 운행 간격 (t:분)
    int max_num;    // 버스 승객 제한 수 (m)
    scanf("%d %d %d", &bus_num, &bus_term, &max_num);
    // 타임 테이블 배열, 다 분으로 고쳐서 넣는다.
    int arr_num; scanf("%d\n", &arr_num);
    int* tt = (int*)malloc(arr_num * sizeof(int));

    // 크루가 대기열에 도착하는 시간 파싱, 처리
    // 버스는 09:00 부터 운행을 시작한다.
    for(int i = 0; i < arr_num; ++i) {
        char _time[6]; scanf("%s", _time);
        int crew_arrival_minute = // 분을 구한다.
            ((_time[0] - '0') * 10 + (_time[1] - '0')) * 60 
        +   ((_time[3] - '0') * 10 + (_time[4] - '0'));

        tt[i] = crew_arrival_minute; // 집어넣는다. 
    }   qsort(tt, arr_num, sizeof(int), compare); // 정렬한다.

    // 버스 도착 시간 또한 분으로 환산해야 한다. & 버스 시간표 배열을 만든다.
    int* bb = (int*)malloc(bus_num * sizeof(int));
    for (int i = 0; i < bus_num; ++i) bb[i] = 540 + bus_term * i;

    int index = 0; // 버스 시간표 전용 index 변수
    int res_time = 0; // 콘이 대기 설 시간
    int man_num = 0; // 현재 몇명의 인원이 탔는가 세어주기 위한 변수

    int i = 0;
    while (i < arr_num) {
        if (tt[i] <= bb[index]) { // 만약 크루의 대기 시간이 오는 편보다 <= 이면
            if (man_num < max_num) { // 그리고, 아직 인원이 덜 찼으면
                if (man_num + 1 == max_num && index + 1 == bus_num) {
                    // 만약, 버스도 마지막 편이고, 인원도 하나만 남았다면 -1 분으로 반환
                    res_time = tt[i] - 1; break;
                }
                else { // 버스가 마지막편이 아니거나, 인원도 덜 찼으면
                    i++; man_num++; // i 와 인원을 하나 늘린다.
                    // 만약, 마지막 번째였다면
                    if (i == arr_num) { res_time = bb[index]; break; }
                }
            }
            else { // 만약, 인원이 찼으면 다음편을 참고하도록 하고, 인원을 초기화
                index++; man_num = 0; }
        }
        else { // 만약 크루의 도착시간이 오는 편보다 > 이면 (반영 안함)
            if (index + 1 == bus_num) { // 마지막 크루가 아닌데도, 마지막 편이라면
                res_time = bb[index]; break; }
            else { index++; man_num = 0; } // 마지막 버스편이 아니라면
        }
    }

    printf("%02d:%02d\n", res_time / 60, res_time % 60); // 출력한다.
    free(bb); free(tt); return 0;
}