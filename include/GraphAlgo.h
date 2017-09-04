//
// Created by mahammad on 8/26/17.
//

#ifndef DB_IMP_SEMINAR_GRAPHALGO_H
#define DB_IMP_SEMINAR_GRAPHALGO_H
#include "Graph.h"

template <class T>
class GraphAlgo {
    int v, e;
    bool* used;
    T* graph;

public:
    GraphAlgo(int v, int e) : v(v), e(e){
        used = new bool[v + 2];
        graph = new T(v, e);
    }

    typedef typename T::iterator iterator;

    void add_edge(int v, std::vector<int>& to);

    void finished();

    void dfs(int v);

    void bfs(int v);

    void dfs_recursion(int v);
};


#endif //DB_IMP_SEMINAR_GRAPHALGO_H
