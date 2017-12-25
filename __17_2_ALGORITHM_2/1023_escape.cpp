#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <functional>

struct Node {
	int destination = -1; int capacity = 0; int flow = 0;
	Node* next_leaf = nullptr; Node* pair_addr = nullptr;
};

void print_nodes(Node* node, int size) {
	for (int i = 0; i < size; ++i) {
		Node* n = &node[i]; printf("S%d : %x : ", i, &node[i]);
		while (true) {
			auto dst = n->destination; auto cap = n->capacity;
			auto flow = n->flow; auto addr = n->pair_addr;

			printf("D%d,C%d,F%d, %x", dst, cap, flow, addr);
			if (n->next_leaf != nullptr) {
				n = n->next_leaf;
				if (n->destination != -1) { printf(" -> %x : ", n); }
				else { printf(" -> x "); break; }
			}
			else break;
		} printf("\n");
	}
}

void insert(Node* node, int dst, int cap) {
	// 이미 있는가 찾는다.
	if (node->destination == dst) { // if there is destination already
		if (node->capacity == 0) node->capacity = cap;
	}
	else { // If there is not destination
		if (node->next_leaf == nullptr) { // Cul de sak
			node->destination = dst; node->capacity = cap;
			node->next_leaf = new Node();
		}
		else {
			insert(node->next_leaf, dst, cap);
		}
	}
}

void find_pair_dst(Node* array, int src, int dst) {
	Node* src_item = &array[src];
	while (src_item != nullptr) {
		if (src_item->destination == dst)
			break;
		else
			src_item = src_item->next_leaf;
	}

	Node* dst_item = &array[dst];
	while (dst_item != nullptr) {
		if (dst_item->destination == src) {
			dst_item->pair_addr = src_item;
			src_item->pair_addr = dst_item;
			break;
		}
		else
			dst_item = dst_item->next_leaf;
	}
}

// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
// ford-folkerson method with edmonds-karp algorithm
// Flow are initialized to 0 whenever each edge is created.
// Weights are set, so we have to use priority_queue instead of general queue.
typedef const int cint; typedef int __id; typedef int __dis;
typedef std::vector<std::pair<int, Node*>> a_path;
typedef std::pair<__id, __dis> d_p;
struct dpOrder { // Need to implement Min priority heap
	bool operator()(d_p const& a, d_p const& b) const {
		return a.second > b.second;
	}
};
#define NOTHING -1

bool get_flag_bsp_exist(Node network[], cint start, cint end, a_path& path) {
	// Set
	std::vector<int> is_visited(end - start + 1), distance(end - start + 1);
	for (auto& dist : distance) dist = 999999;
	distance[start] = 0;

	std::priority_queue<d_p, std::vector<d_p>, dpOrder> queue;
	is_visited[start] = 1; queue.push(std::make_pair(start, 0));

	while (!queue.empty()) { // Start
							 // Put it out.
		auto obj = queue.top(); queue.pop();
		cint src_id = obj.first; int dist = obj.second;
		Node* node = &network[src_id];

		// Check each adjecent edge of source node.
		while (node->destination != NOTHING) {
			int dst = node->destination;
			int res_cap = node->capacity - node->flow; // always get positive
			if (is_visited[dst] != 2 &&
				path[dst].first == NOTHING && dst != start && res_cap > 0) {
				is_visited[dst] = 1;

				if (dist + res_cap < distance[dst]) {
					distance[dst] = dist + res_cap;
					path[dst].first = src_id; path[dst].second = node;
					//printf("%d -> %d with %d\n", src_id, dst, distance[dst]);
					queue.push(std::make_pair(dst, distance[dst]));
				}
			}
			node = node->next_leaf;
		}

		is_visited[src_id] = 2;
	}

	// Check
	if (path[end].first != NOTHING) return true;
	else                            return false;
}

int find_residual_cap(a_path& path, cint start, cint end) {
	int min = 999999; int p_idx = end;

	while (path[p_idx].first != -1) {
		Node* node = path[p_idx].second;
		int residual_cap = node->capacity - node->flow;

		if (min > residual_cap) min = residual_cap;
		p_idx = path[p_idx].first;
	}

	return min;
}

void reflect_flow(int res_cap, a_path& path) {
	int size = path.size();
	auto& pair = path[size - 1];
	while (pair.first != -1) {
		Node* node = pair.second;
		auto dst = node->destination; auto cap = node->capacity;
		auto flow = node->flow; auto addr = node->pair_addr;
		//printf("S%d, D%d,C%d,F%d, %x\n", pair.first, dst, cap, flow, addr);

		int f = 0;
		do { // 간선에 있는 edge 만 뽑아서 넣는다.
			if (node->capacity == 0) node->flow -= res_cap; // If not network
			else node->flow += res_cap; // If in network

			node = node->pair_addr; f++;
		} while (f != 2);

		pair = path[pair.first];
	}
}

void process(Node network[], cint start, cint end) {
	// Initialization
	a_path augmented_path; augmented_path.resize(end - start + 1);
	for (auto& item : augmented_path) item.first = NOTHING;

	// Loop
	while (get_flag_bsp_exist(network, start, end, augmented_path)) {
		// Find min residual capacity
		auto min = find_residual_cap(augmented_path, start, end);
		reflect_flow(min, augmented_path);
		for (auto& item : augmented_path) item.first = NOTHING;
	}
}

#define NOT_SRC 0
#define SRC 1
typedef int __dst;

struct EdgeInfo { std::vector<__dst> destinations; };
int num_node = 0, num_edge = 1, diagonal_num = 0; 

void process_diagonal_to_edge(std::vector<EdgeInfo>& edge_info, std::vector<std::vector<int>>& diagonal_arr) {
	for (int y = 0; y < diagonal_num; ++y) {
		for (int x = 0; x < diagonal_num; ++x) {
			auto mine = y * diagonal_num + x;
			auto mine_exit	= 2 * (mine + 1);
			
			// Internal Edge
			edge_info[mine_exit - 1].destinations.push_back(mine_exit);
			num_edge += 1;

			// If node is on edge (모서리에 있으면), add 1 for exit node to sink
			if (x == 0 || x == diagonal_num - 1 || 
				y == 0 || y == diagonal_num - 1) {
				edge_info[mine_exit].destinations.push_back(num_node + 1);
				num_edge += 1;
			}

			// If node is source, add 1 for enter node from source '0'
			if (diagonal_arr[y][x] == SRC) { 
				edge_info[0].destinations.push_back(mine_exit - 1);
				num_edge += 1;
			}

			// And, add edges between one's exit node to other's enter node.
			if (x != 0) { 
				edge_info[mine_exit].destinations.push_back(mine_exit - 3);
				num_edge += 1;
			};
			if (y != 0) {
				edge_info[mine_exit].destinations.push_back(2 * ((y - 1) * diagonal_num + x) + 1); 
				num_edge += 1;
			};
			if (x != diagonal_num - 1) {
				edge_info[mine_exit].destinations.push_back(mine_exit + 1);
				num_edge += 1;
			}
			if (y != diagonal_num - 1) {
				edge_info[mine_exit].destinations.push_back(2 * ((y + 1) * diagonal_num + x) + 1);
				num_edge += 1;
			}
		}
	}
}

void print_list(std::vector<EdgeInfo>& edge_info) {
	FILE* p_file = fopen("output.txt", "w");
	fprintf(p_file, "%d %d\n", num_node, num_edge);

	for (int src = 0; src < edge_info.size(); ++src) {
		for (int dst : edge_info[src].destinations) {
			fprintf(p_file, "%d %d %d\n", src, dst, 1);
		}
	}

	fclose(p_file);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
	// Initiate
	std::cin >> diagonal_num;
	std::vector<std::vector<int>> diagonal_arr(diagonal_num);
	for (auto& sub_arr : diagonal_arr) { 
		sub_arr = std::vector<int>(diagonal_num); 
	}

	// Input
	std::string arr; std::getline(std::cin, arr);

	int sources = 0;
	for (int y = 0; y < diagonal_num; ++y) { 
		std::getline(std::cin, arr);
		const char* _str = arr.c_str();
		for (int x = 0; x < diagonal_num; ++x) {
			auto value = 0; value = _str[x] - '0'; 
			if (value == SRC) sources += 1;
			diagonal_arr[y][x] = value; 
		}
	}
	fflush(stdin);

	// soruce to block, inner corridor, edge to sync, undirected edges
	// first, calculate the number of nodes and edges
	// Check out if node is on edge (모서리)
	num_node = diagonal_num * diagonal_num * 2;  
	num_edge = 0;
	
	std::vector<EdgeInfo> edge_info(num_node + 2);
	process_diagonal_to_edge(edge_info, diagonal_arr);
	print_list(edge_info);

	// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** ***
	// 생산자 소비자를 제외한 노드 수와 edge 수를 받는다.
	// 배열을 생성한다. 생성자 및 소비자 포함.
	freopen("output.txt", "r", stdin);

	scanf("%d %d", &num_node, &num_edge);
	printf("%d %d\n", num_node, num_edge);
	Node* flow_array = new Node[num_node + 2];

	// Input and make Network
	for (int i = 0; i < num_edge; ++i) {
		int src, dst, cap; scanf("%d %d %d", &src, &dst, &cap);

		insert(&flow_array[src], dst, cap); insert(&flow_array[dst], src, 0);
		find_pair_dst(flow_array, src, dst);
	}

	// Just print there are well.
	print_nodes(flow_array, num_node + 2);
	// Process to maximize flow.
	process(flow_array, 0, num_node + 2 - 1);
	puts(""); print_nodes(flow_array, num_node + 2); // Result

	int max_flow = 0;
	Node* flow = &flow_array[num_node + 2 - 1];
	while (flow->destination != -1) {
		max_flow -= flow->flow;
		flow = flow->next_leaf;
	}

	FILE* p_f = fopen("result_4.txt", "w+");
	fprintf(p_f, "Start : %d %s Max : %d\n%s", sources,
		(sources == max_flow) ? "==" : "!=", max_flow,
		(sources == max_flow) ? "Escape Success" : "Escape Failed");
	fclose(p_f);
	return 0;
}