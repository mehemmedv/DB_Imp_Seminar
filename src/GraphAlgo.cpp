//
// Created by mahammad on 8/26/17.
//

#include <cstring>
#include <queue>
#include <climits>
#include <set>
#include <iostream>
#include "../include/GraphAlgo.h"

template <class T>
#if VERIFY_ENABLED == false
void GraphAlgo<T>::bfs(int cur_vertex) {
#else
std::vector<int> GraphAlgo<T>::bfs(int cur_vertex) {
    std::vector<int> res;
#endif
    memset(used, 0, sizeof(bool) * (v + 2));
    std::queue<int> q;
    q.push(cur_vertex);
    used[cur_vertex] = true;
    while(!q.empty()){
        cur_vertex = q.front();
#if VERIFY_ENABLED == true
        res.push_back(cur_vertex);
#endif
        q.pop();
        auto it_end = graph->end(cur_vertex);
        for(auto it = graph->begin(cur_vertex); it != it_end; ++it){
            if(!used[*it])
                used[*it] = true, q.push(*it);
        }
    }
#if VERIFY_ENABLED == true
    return res;
#endif
}

template <class T>
#if VERIFY_ENABLED == false
    void GraphAlgo<T>::dfs_recursion(int cur_vertex) {
#else
    void GraphAlgo<T>::dfs_recursion(int cur_vertex, std::vector<int>& res) {
    res.push_back(cur_vertex);
#endif
    used[cur_vertex] = true;
    auto it_end = graph->end(cur_vertex);
    for(auto it = graph->begin(cur_vertex); it != it_end; ++it){
        if(!used[*it]){
#if VERIFY_ENABLED == false
            dfs_recursion(*it);
#else
            dfs_recursion(*it, res);
#endif
        }
    }
}

template <class T>
#if VERIFY_ENABLED == false
void GraphAlgo<T>::dfs(int cur_vertex) {
#else
    std::vector<int> GraphAlgo<T>::dfs(int cur_vertex) {
    std::vector<int> res;
#endif
    memset(used, 0, sizeof(bool) * (v + 2));
#if VERIFY_ENABLED == false
    dfs_recursion(cur_vertex);
#else
    dfs_recursion(cur_vertex, res);
    return res;
#endif
}

template <class T>
void GraphAlgo<T>::add_edge(int v, std::vector<int>& to, std::vector<int>& weights){
    graph->add_edge(v, to, weights);
}

template <class T>
void GraphAlgo<T>::add_edge(int from, int to, int weight) {
    graph->add_edge(from, to, weight);
}

template <class T>
void GraphAlgo<T>::finished() {
    graph->finished();
}

template <class T>
long long GraphAlgo<T>::dijiksta(int from, int to) {
    for(int i = 0; i < v + 2; ++i)
        dist[i] = LONG_LONG_MAX;
    dist[from] = 0;

    std::set<std::pair<long long, int>> min_heap;
    min_heap.insert(std::make_pair(0, from));

    while(!min_heap.empty()){
        std::pair<long long, int> temp = *(min_heap.begin());
        min_heap.erase(min_heap.begin());
        long long distance = temp.first;
        int cur_vertex = temp.second;
        auto it_end = graph->end(cur_vertex);
        auto it_w = graph->begin_weights(cur_vertex);
        int cnt = 0;
        for(auto it = graph->begin(cur_vertex); it != it_end; ++it, ++it_w){
            int cur_weight = *it_w;
            int to_vertex = *it;
            ++cnt;
            if(distance + cur_weight < dist[to_vertex]){
                if(min_heap.find(std::make_pair(dist[to_vertex], to_vertex)) != min_heap.end())
                    min_heap.erase(min_heap.find(std::make_pair(dist[to_vertex], to_vertex)));
                dist[to_vertex] = distance + cur_weight;
                min_heap.insert(std::make_pair(dist[to_vertex], to_vertex));
            }
        }
    }

    return dist[to];
}