//
// Created by mahammad on 8/26/17.
//

#ifndef DB_IMP_SEMINAR_GRAPHALGO_H
#define DB_IMP_SEMINAR_GRAPHALGO_H

template <class T>
class GraphAlgo {
    int v, e;
    long long* dist;
    bool* used;
    T* graph;

public:
    GraphAlgo(int v, int e) : v(v), e(e){
        used = new bool[v + 2];
        graph = new T(v, e);
        dist = new long long [v + 2];
    }

    void add_edge(int v, std::vector<int>& to, std::vector<int>& weights);

    void add_edge(int from, int to, int weight);

    void finished();

    void dfs(int v);

    void bfs(int v);

    void dfs_recursion(int v);

    long long dijiksta(int from, int to);
};


#endif //DB_IMP_SEMINAR_GRAPHALGO_H
