#include <iostream>
#include <iomanip>
#include <chrono>

#include <vector>
#include <numeric>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;
using namespace std::chrono;

#define LIMIT 7
#define FILE_NAME "X1.txt"
#define WARD // IF you want to not use WARD, do comment this line.

const int x = 0, y = 1;
using Position = std::vector<int>;

class Item {
public:
    Item(int id, Position pos) : id(id), pos(pos) {};

    const int operator[](int i) const { return pos.at(i); }
    const unsigned size() const { return pos.size(); }
    const unsigned get_id() const { return id; }

    void set_lv(int i) { level = i; }
    const unsigned get_lv() const { return level; }

    int cluster = -1;

private:
    int id = 0;
    unsigned level = 0;
    const std::vector<int> pos;
};

struct Cluster {
    unsigned level = 0;
    unsigned id = 0;
    vector<Item*> items;
    vector<std::pair<Cluster*, double>> distances;
};

class DisjointSet {
public:
    DisjointSet(decltype(std::vector<int>().size()) tree_size);
    ~DisjointSet() = default;

    unsigned collapsing_find(const unsigned index);
    void weighted_union(const unsigned lhs, const unsigned rhs);

    void print_tree();

private:
    vector<int> tree_parent;

public:
    DisjointSet(DisjointSet&) = delete;
    DisjointSet operator=(DisjointSet&) = delete;
};

DisjointSet::DisjointSet(decltype(std::vector<int>().size()) tree_size) :
    tree_parent(tree_size + 1, -1) { }

unsigned DisjointSet::collapsing_find(const unsigned index) {
    auto result_index = index;
    while (tree_parent[result_index] > 0) { result_index = tree_parent[result_index]; }

    auto swap_index = index;
    while (result_index != swap_index) {
        auto source = tree_parent[swap_index];
        tree_parent[swap_index] = result_index;
        swap_index = source;
    }

    return result_index;
}

void DisjointSet::weighted_union(const unsigned lhs, const unsigned rhs) {
    int node_summary = tree_parent[lhs] + tree_parent[rhs];

    if (tree_parent[lhs] > tree_parent[rhs]) {
        tree_parent[lhs] = rhs;
        tree_parent[rhs] = node_summary;
    }
    else {
        tree_parent[rhs] = lhs;
        tree_parent[lhs] = node_summary;
    }
}

void DisjointSet::print_tree() {
    for (decltype(tree_parent.size()) i = 0; i < tree_parent.size(); ++i)
        cout << setw(5) << i;
    cout << '\n';

    for (decltype(tree_parent.size()) i = 0; i < tree_parent.size(); ++i)
        cout << setw(5) << tree_parent[i];
    cout << '\n';
}

/******************************************************************************
* Main
*/

using ItemArray = vector<Item>;
using ClusterArray = vector<Cluster>;
using DistanceArray = vector<Cluster*>;

void initialize_items(ClusterArray& item_array, int, int, ItemArray& items);
void calculate_distance(DistanceArray& distances);
double get_distance(const Cluster& lhs, const Cluster& rhs);
void check_shortest_distance(DistanceArray&, unsigned* x_id, unsigned* y_id);
// inline void print_distances(const DistanceArray& distances);
bool check_cluster_hit_limit(const ItemArray& items, int size, int limit);

int main() {
    ios_base::sync_with_stdio(false);


    freopen(FILE_NAME, "r", stdin); // Read File


    unsigned dim, item_num; cin >> item_num >> dim; // Dimension and The number of items
    // Input and Create Item Informations
    ItemArray items;         items.reserve(item_num + 1);
    ClusterArray clusters;   clusters.reserve(item_num + 1);
    initialize_items(clusters, item_num, dim, items);

    // Create Set
    DisjointSet set(item_num);

    // Start Check time
    auto start_time = std::chrono::system_clock::now();

    // First, get Distances of each pair.
    DistanceArray distances;
    for (auto& cluster : clusters) { distances.push_back(&cluster); }
    calculate_distance(distances);

    // ************************************************************************
    // Process
    while (!check_cluster_hit_limit(items, item_num, LIMIT)) { // at least loop N - 1 times
        unsigned y_id, x_id;
        check_shortest_distance(distances, &x_id, &y_id);

        auto y_root = set.collapsing_find(distances[y_id]->items[0]->get_id());
        auto x_root = set.collapsing_find(distances[x_id]->items[0]->get_id());

        if (y_root != x_root) {
            set.weighted_union(x_root, y_root);

            auto id = ((distances[y_id]->id < distances[x_id]->id) ? distances[y_id]->id : distances[x_id]->id);

            // 관련된 거리도 지운다.
            for (auto& row : distances) {
                if (row == nullptr) continue;

                auto& dist_array = row->distances;
                if (dist_array.size() >= y_id) { dist_array.erase(dist_array.begin() + y_id - 1); }
                if (dist_array.size() >= x_id) { dist_array.erase(dist_array.begin() + x_id - 1); }
            }

            // Cluster 을 만든다, Cluster 에 합칠 item 들을 넣는다.
            Cluster cluster; cluster.id = id;

            for (auto& item : clusters[x_id].items) { 
                item->cluster = id;
                cluster.items.push_back(item);
            }
            for (auto& item : clusters[y_id].items)  {
                item->cluster = id;
                cluster.items.push_back(item);
            }

            // 대상 Cluster 을 지운다.
            clusters.erase(clusters.begin() + y_id);
            clusters.erase(clusters.begin() + x_id);
            clusters.push_back(cluster);

            // 거리 배열을 지우고 다시 만든다.
            distances = DistanceArray();
            for (auto& cluster : clusters) { distances.push_back(&cluster); }

            // 맨 마지막 행만 새로 계산한다.
            auto& source = *distances.rbegin();
            for (auto& target : distances) {
                if (target == distances[0]) continue;
                if (source == target) {
                    source->distances.push_back(make_pair(static_cast<Cluster*>(nullptr), 0));
                    continue;
                }

                auto distance_info = make_pair(target, get_distance(*source, *target));
                source->distances.push_back(distance_info);
            }
        }
    }

    vector<int> counts(item_num + 1);
    for (auto i = 1u; i <= item_num; ++i) counts[items[i].cluster]++;

    vector<pair<unsigned, int>> picked_counts; picked_counts.reserve(7);
    for (auto i = 1u; i <= item_num; ++i) { 
        if (counts[i] != 0) { 
            picked_counts.push_back(make_pair(i, counts[i]));
        }
    };
    
    sort(picked_counts.begin(), picked_counts.end(), 
        [](const pair<unsigned, int>& lhs, const pair<unsigned, int>& rhs) {
            return lhs.second > rhs.second;
    });

    // End Check time and Return ellapsed time to milliseconds.
    auto end_time = std::chrono::system_clock::now();
    auto elapsed_time = duration_cast<microseconds>(end_time - start_time);
    cout << "Elapsed Time : " << setprecision(6) << elapsed_time.count() / 1e+3 << " milliseconds\n";

    {   // Output Results
        cout << "C = " << LIMIT << " N = ( ";
        for (const auto& index_pair : picked_counts) { cout << index_pair.second << ' '; }
        cout << ")\n";

        for (auto j = 1u; j <= item_num; ++j) {
            auto& item = items[j];

            auto i = 0u;
            while (i < LIMIT) { if (item.cluster == picked_counts[i].first) break; else ++i; }
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }
}

void initialize_items(ClusterArray& item_array, int item_num, int dim, ItemArray& items) {
    // First is Dummy
    items.push_back(Item(0, vector<int>(dim, 0u)));
    Cluster dummy;
    dummy.items.push_back(&items[0]);
    item_array.push_back(dummy);

    // Make Set
    for (int i = 1; i <= item_num; ++i) {
        vector<int> position;
        for (int j = 1; j <= dim; ++j) { auto value = 0; cin >> value; position.push_back(value); }

        Item item(i, position);
        item.cluster = i;
        items.push_back(item);

        Cluster cluster;
        cluster.items.push_back(&items[i]);
        cluster.id = i;

        item_array.push_back(cluster);
    }
}

void calculate_distance(DistanceArray& distances) {
    auto size = distances.size() - 1;

    for (auto i = 1u; i <= size; ++i) {
        auto source_cluster = distances[i];

        for (auto j = 1u; j <= i; ++j) {
            auto destination_cluster = distances[j];
            if (source_cluster == destination_cluster) {
                source_cluster->distances.push_back(make_pair(static_cast<Cluster*>(nullptr), 0.));
                continue;
            }

            auto distance_info = make_pair(destination_cluster,
                get_distance(*source_cluster, *destination_cluster));
            source_cluster->distances.push_back(distance_info);
        }
    }
}

inline double get_distance(const Cluster& lhs, const Cluster& rhs) {
    auto result = numeric_limits<double>::max();
    auto l_size = lhs.items.size();
    auto r_size = rhs.items.size();
    auto offset = 1.;
    
#ifdef WARD
    double lhs_sz = static_cast<double>(lhs.items.size());
    double rhs_sz = static_cast<double>(rhs.items.size());
    offset = lhs_sz * rhs_sz / (lhs_sz + rhs_sz);
#endif

    for (auto i = 0u; i < l_size; ++i) {
        for (auto j = 0u; j < r_size; ++j) {
            auto value = 0.;
            for (auto k = 0u; k < 2; ++k) {
                value += pow((*lhs.items[i])[k] - (*rhs.items[j])[k], 2);
            }

            if (value < result) { // 만약 가장 짧은 거리를 구했다면 
                result = value;
            }
        }
    }

    return offset * sqrt(result);
}

void check_shortest_distance(DistanceArray& distances, unsigned* x_id, unsigned* y_id) {
    double result = numeric_limits<double>::max();

    int y = -1;
    for (const auto& y_cluster : distances) {
        ++y;

        if (y_cluster == nullptr) continue;

        int x = 0;
        for (const auto& x_pair : y_cluster->distances) {
            ++x;

            // auto& x_cluster = *x_pair.first;
            auto  distance = x_pair.second;

            if (distance != 0 && distance < result) {
                *y_id = y; *x_id = x; result = distance;
            }
        }
    }
}

bool check_cluster_hit_limit(const ItemArray& items, int size, int limit) {
    vector<int> counts(size + 1);
    for (auto i = 1u; i <= size; ++i)
        counts[items[i].cluster]++;

    auto the_number = 0u;
    for (const auto& count : counts) { if (count != 0) the_number++; }

    if (the_number <= limit) return true; else return false;
}

// DONE! (maybe)

// void print_distances(const DistanceArray& distances) {
//     cout << "     ";
//     for (auto y = 1u; y < distances.size(); ++y) cout << setw(5) << y;
//     cout << '\n';

//     for (auto y = 1u; y < distances.size(); ++y) {
//         cout << setw(5) << y;
//         for (const auto& pair : distances[y]->distances) {
//             cout << setw(5) << setprecision(3) << pair.second;
//         }
//         cout << '\n';
//     }
// }