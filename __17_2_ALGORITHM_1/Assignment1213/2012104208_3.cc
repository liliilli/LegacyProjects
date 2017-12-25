#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define LEFT_LIMIT -987654
#define RIGHT_LIMIT 987654

struct Edge {
    unsigned dest_index;
    unsigned distance;

    Edge() : dest_index(0), distance(0) {};
    Edge(const unsigned dest_index, const unsigned distance)
            : dest_index(dest_index), distance(distance) {};
};

struct Position {
    int pos;
    unsigned node_index;
    unsigned layer;

    unsigned distance = 98765432;
    Position* parent_index = nullptr;
    std::vector<Edge> edges;

    Position(const int pos, const unsigned node_index, const unsigned layer) 
            : pos(pos), node_index(node_index), layer(layer) {};
};

int main() {
    std::ios_base::sync_with_stdio(false);
    // freopen("prob_3_input.txt", "r", stdin);

    // ************************************************************************
    // Input
    // ************************************************************************
    int layer_number, plate_width;
    std::cin >> layer_number >> plate_width;

    // 맨 처음은 Input 용, 맨 마지막은 Output 용.
    std::vector<std::vector<Position>> positions(layer_number + 2);
    auto index = 0u;
    auto y = 0u;
    positions[0].push_back(Position(plate_width / 2, index++, y)); ++y;

    // 우선 모든 레이어의 모든 위치를 넣는다.
    while (true) {
        int number; std::cin >> number;
        if (number == -1) break;
        else {
            for (auto i = 0; i < number; ++i) {
                int pos = 0; std::cin >> pos;
                positions[y].push_back(Position(pos, index++, y));
            }
        }
        ++y;
    }

    // 출구용 Output 위치를 넣는다. 마지막 계층에서 Output 까지의 거리는 모두 0 이다.
    (positions.end() - 1)->push_back(Position(plate_width / 2, index++, y));

    // ************************************************************************
    // Make Graph
    // ************************************************************************
    // 기본 방향은 각 source 위치에 대해 가장 가까운 다음 계층의 위치만을 골라 Graph 로 연결한다.
    // 따라서 좌, 우 2방향 (boundary 체크 포함) 또는 직통 (1개) 로만 구성될 것이다.
    for (auto it = positions.begin(); it < positions.end() - 1; it++) {
        for (auto& source : *it) {
            // Left 혹은 앙 위치 노드를 찾는다. 없으면 pass 한다.
            auto left   = LEFT_LIMIT;  Position* next_left = nullptr;
            auto right  = RIGHT_LIMIT;   Position* next_right = nullptr; 

            for (auto& dest : *(it + 1)) {
                auto dist_value = dest.pos - source.pos; 
                if (dist_value <= 0) { // Left 이면
                    if (left < dist_value) {
                        left = dist_value;
                        next_left = &dest;
                    }

                    if (left == 0) break; // 만약 중앙으로 직통하는 슬릿이 있으면 바로 Edge을 만든다.
                }
                else { // Right 이면
                    if (dist_value < right) {
                        right = dist_value;
                        next_right = &dest;
                    }
                }
            }

            if (next_left != nullptr) {
                unsigned distance = 0;
                // 여기서, 현재 층이 마지막 층 바로 직전 층인지 검사한다.
                if (it != positions.end() - 2) { distance = -left; }
                source.edges.push_back(Edge(next_left->node_index, distance));
            }
            
            if (next_right != nullptr) {
                unsigned distance = 0;
                if (it != positions.end() - 2) { distance = right; }
                source.edges.push_back(Edge(next_right->node_index, distance));
            }
        }
    }

    // ************************************************************************
    // Dijkstra Algorithm with priority queue
    // ************************************************************************
    // Dijkstra 을 쓰기 위한 기본 세팅
    std::vector<Position*> nodes;
    for (auto& row : positions) {
        for (auto& item : row) {
            nodes.push_back(&item);
        }
    }
 
    auto cmp = [](const Position* lhs, const Position* rhs) { 
        return lhs->distance <= rhs->distance; 
    };
    std::priority_queue<Position*, std::vector<Position*>, decltype(cmp)> dist_queue(cmp);
    nodes[0]->distance = 0;
    dist_queue.push(nodes[0]);
   
    // Dijkstra procedure
    while (!dist_queue.empty()) {
        auto& source = *dist_queue.top();
        dist_queue.pop();

        for (const auto& edge : source.edges) {
            auto ref_distance   = source.distance + edge.distance;
            auto& destination   = *nodes[edge.dest_index];

            if (ref_distance < destination.distance) {
                destination.distance        = ref_distance;
                destination.parent_index    = &source;
                dist_queue.push(nodes[edge.dest_index]);
            }
        }
    }

    // ************************************************************************
    // Print
    // ************************************************************************
    // 맨 처음부터 출력하기 위해 리스트에 경로를 넣는다.
    auto* parent = (*(nodes.end() - 1))->parent_index;
    std::vector<int> path;
    while (parent != nullptr) {
        path.push_back(parent->pos);
        parent = parent->parent_index;
    }

    // 출력한다.
    std::cout << (*nodes.crbegin())->distance << ' ';
    for (auto it = path.end() - 2; it != path.begin() - 1; --it) {
        std::cout << *it << ' ';
    }

    return 0;
}