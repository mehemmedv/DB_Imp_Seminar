//
// Created by mahammad on 8/21/17.
//

#include "../include/CSRGraph.h"

void CSRGraph::add_edges(int from, int to) {
    if (from != last_vertex)
        offsets[last_vertex] = cur_idx, last_vertex = from;
    edges[cur_idx++] = to;
}

void CSRGraph::set_offset() {
    offsets[v + 1] = cur_idx;
}

void CSRGraph::bfs(int v) {
    used = new bool[v + 2];
    memset(used, 0, sizeof(int) * (v + 2));

    std::queue<int> q;
    q.push(v);

    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();
        for (int i = offsets[cur_vertex]; i < offsets[cur_vertex + 1]; ++i) {
            if (!used[edges[i]])
                q.push(edges[i]), used[edges[i]] = true;
        }
    }
    delete[] used;
}

void CSRGraph::dfs_recur(int v) {
    used[v] = true;
    for (int i = offsets[v]; i < offsets[v + 1]; ++i)
        if (!used[edges[i]])
            dfs_recur(edges[i]);
}

void CSRGraph::dfs(int v) {
    used = new bool[v + 2];
    memset(used, 0, sizeof(int) * (v + 2));
    dfs_recur(v);
    delete[] used;
}