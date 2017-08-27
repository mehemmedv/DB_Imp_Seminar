//
// Created by mahammad on 8/26/17.
//

#ifndef DB_IMP_SEMINAR_GRAPHALGO_H
#define DB_IMP_SEMINAR_GRAPHALGO_H
#include "Graph.h"


class GraphAlgo {
    int v;
    bool* used;
    Graph* graph;
public:
    GraphAlgo(int v, Graph* graph) : v(v), graph(graph){
        used = new bool[v + 2];
    }

    void dfs(int v);

    void bfs(int v);

    void dfs_recursion(int v);
};


#endif //DB_IMP_SEMINAR_GRAPHALGO_H
