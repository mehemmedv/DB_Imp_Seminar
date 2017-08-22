//
// Created by mahammad on 8/21/17.
//

#include "../include/ALGraph.h"

void ALGraph::add_edge(int from, int to) {
    edges[from].push_front(to);
}

void ALGraph::bfs(int v) {
    used = new bool[v + 2];
    memset(used, 0, sizeof(int) * (v + 2));

    std::queue<int> q;
    q.push(v);

    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();
        for (int to : edges[cur_vertex])
            if (!used[to])
                q.push(to), used[to] = true;
    }
    delete[] used;
}

void ALGraph::dfs_recur(int v) {
    used[v] = true;
    for (int to : edges[v])
        if (!used[to])
            dfs_recur(to);
}

void ALGraph::dfs(int v) {
    used = new bool[v + 2];
    memset(used, 0, sizeof(int) * (v + 2));
    dfs_recur(v);
    delete[] used;
}