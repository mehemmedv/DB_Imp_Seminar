//
// Created by mahammad on 8/26/17.
//

#include <cstring>
#include <queue>
#include "../include/GraphAlgo.h"

template <class T>
void GraphAlgo<T>::bfs(int cur_vertex) {
    //used = new bool[v + 2];
    std::memset(used, 0, sizeof(bool) * (v + 2));

    std::queue<int> q;
    q.push(cur_vertex);
    used[cur_vertex] = true;
    while(!q.empty()){
        cur_vertex = q.front();
        q.pop();
        int to;
        while(graph->next_neighbor(cur_vertex, to)){
            if(!used[to])
                used[to] = true, q.push(to);
        }
    }
    //delete[] used;
}

template <class T>
void GraphAlgo<T>::dfs_recursion(int cur_vertex) {
    used[cur_vertex] = true;
    int to;

    /*while(graph->next_neighbor(cur_vertex, to)){
        if(!used[to])
            used[to] = true, dfs_recursion(to);
    }*/

    for(auto it = graph->begin(cur_vertex); it != graph->end(cur_vertex); ++it){
        if(!used[*it])
            used[*it] = true, dfs_recursion(*it);
    }
}

template <class T>
void GraphAlgo<T>::dfs(int cur_vertex) {
    //used = new bool[v + 2];
    memset(used, 0, sizeof(bool) * (v + 2));
    dfs_recursion(cur_vertex);
    //delete[] used;
}

template <class T>
void GraphAlgo<T>::add_edge(int v, std::vector<int>& to){
    graph->add_edge(v, to);
}

template <class T>
void GraphAlgo<T>::finished() {
    graph->finished();
}



