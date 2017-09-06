//
// Created by mahammad on 8/26/17.
//

#include <cstring>
#include <queue>
#include "../include/GraphAlgo.h"

template <class T>
void GraphAlgo<T>::bfs(int cur_vertex) {
    memset(used, 0, sizeof(bool) * (v + 2));

    std::queue<int> q;
    q.push(cur_vertex);
    used[cur_vertex] = true;
    while(!q.empty()){
        cur_vertex = q.front();
        q.pop();
        auto it_end = graph->end(cur_vertex);
        for(auto it = graph->begin(cur_vertex); it != it_end; ++it){
            if(!used[*it])
                used[*it] = true, q.push(*it);
        }
    }
}

template <class T>
void GraphAlgo<T>::dfs_recursion(int cur_vertex) {
    used[cur_vertex] = true;
    auto it_end = graph->end(cur_vertex);
    for(auto it = graph->begin(cur_vertex); it != it_end; ++it){
        if(!used[*it])
            dfs_recursion(*it);
    }
}

template <class T>
void GraphAlgo<T>::dfs(int cur_vertex) {
    memset(used, 0, sizeof(bool) * (v + 2));
    dfs_recursion(cur_vertex);
}

template <class T>
void GraphAlgo<T>::add_edge(int v, std::vector<int>& to){
    graph->add_edge(v, to);
}

template <class T>
void GraphAlgo<T>::finished() {
    graph->finished();
}



