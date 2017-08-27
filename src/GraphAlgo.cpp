//
// Created by mahammad on 8/26/17.
//

#include <cstring>
#include <queue>
#include "../include/GraphAlgo.h"

void GraphAlgo::bfs(int cur_vertex) {
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

void GraphAlgo::dfs_recursion(int v) {
    used[v] = true;
    int to;
    while(graph->next_neighbor(v, to)){
        if(!used[to])
            used[to] = true, dfs_recursion(to);
    }
}

void GraphAlgo::dfs(int cur_vertex) {
    //used = new bool[v + 2];
    memset(used, 0, sizeof(bool) * (v + 2));
    dfs_recursion(cur_vertex);
    //delete[] used;
}

