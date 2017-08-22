//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_ALGRAPH_H
#define DB_IMP_SEMINAR_ALGRAPH_H

// Adjacency list implementation of Graph
class ALGraph {
    list<int> *edges;
    int v;

    void dfs_recur(int v);

public:
    ALGraph(int v) : v(v) {
        edges = new list<int>[v];
    }

    void add_edge(int from, int to);

    void bfs(int v);

    void dfs(int v);
};


#endif //DB_IMP_SEMINAR_ALGRAPH_H
