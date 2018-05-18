//
// Created by mahammad on 8/26/17.
//

#ifndef DB_IMP_SEMINAR_GRAPHALGO_H
#define DB_IMP_SEMINAR_GRAPHALGO_H

#include <cstring>
#include <queue>
#include <climits>
#include <set>

#define VERIFY_ENABLED false

template<typename T>
class GraphAlgo {
    uint64_t v, e;
    uint64_t *dist;
    bool *used;
    T *graph;

public:
    GraphAlgo(uint64_t v, uint64_t e) : v(v), e(e) {
        used = new bool[v + 2];
        graph = new T(v, e);
        dist = new uint64_t[v + 2];
    }

    ~GraphAlgo() {
        //std::cout<<"Graph Algo delete"<<std::endl;
        delete[] dist;
        delete[] used;
        delete graph;
    }

    // void add_edge(int v, std::vector<int>& to, std::vector<int>& weights);

    // void add_edge(int from, int to, int weight);

    // void finished();

    inline void sortByEdgesByNodeId() {
        graph->sortByEdgesByNodeId();
    }

    int bfs(int cur_vertex) {
        uint64_t sum = 0;
        memset(used, 0, sizeof(bool) * (v + 2));
        std::queue<int> q;
        q.push(cur_vertex);
        used[cur_vertex] = true;
        while (!q.empty()) {
            cur_vertex = q.front();
            q.pop();
            auto it_weight = graph->begin_weights(cur_vertex);
            for (int to : graph->get_neighbors(cur_vertex)) {
                if (!used[to]) {
                    used[to] = true, q.push(to), graph->get_weight(cur_vertex, to, it_weight);
                }
                ++it_weight;
            }
        }
        //std::cout << "sum: " << sum << "\n";

        return sum;

    }

    int dfs_recursion(int cur_vertex) {
        uint64_t sum = 0;
        used[cur_vertex] = true;
        auto it_weight = graph->begin_weights(cur_vertex);
        for (int to : graph->get_neighbors(cur_vertex)) {
            if (!used[to]) {
                sum += dfs_recursion(to), sum += graph->get_weight(cur_vertex, to, it_weight);
            }
            ++it_weight;
        }
        return sum;
    }

    int dfs(int cur_vertex) {
        memset(used, 0, sizeof(bool) * (v + 2));
        return dfs_recursion(cur_vertex);
    }

    void add_edge(int v, std::vector<int> &to, std::vector<int> &weights) {
        graph->add_edge(v, to, weights);
    }

    void add_edge(int from, int to, int weight) {
        graph->add_edge(from, to, weight);
    }

    void finished() {
        graph->finished();
    }

    uint64_t dijkstra(int from, int to) {
        for (int i = 0; i < v + 2; ++i)
            dist[i] = LONG_LONG_MAX;
        dist[from] = 0;

        std::set<std::pair<long long, int>> min_heap;
        min_heap.insert(std::make_pair(0, from));

        while (!min_heap.empty()) {
            std::pair<uint64_t , int> temp = *(min_heap.begin());
            min_heap.erase(min_heap.begin());
            uint64_t distance = temp.first;
            int cur_vertex = temp.second;
            auto it_w = graph->begin_weights(cur_vertex);
            int cnt = 0;
            for (int to_vertex : graph->get_neighbors(cur_vertex)) {
                //int cur_weight = *it_w;
                int cur_weight = graph->get_weight(cur_vertex, to_vertex, it_w);
                //int to_vertex = *it;
                ++cnt;
                if (distance + cur_weight < dist[to_vertex]) {
                    auto it_find = min_heap.find(std::make_pair(dist[to_vertex], to_vertex));
                    if (it_find != min_heap.end())
                        min_heap.erase(it_find);
                    dist[to_vertex] = distance + cur_weight;
                    min_heap.insert(std::make_pair(dist[to_vertex], to_vertex));
                }
                ++it_w;
            }
        }

        return dist[to];
    }
};

#endif //DB_IMP_SEMINAR_GRAPHALGO_H
