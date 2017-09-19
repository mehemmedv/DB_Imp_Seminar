//
// Created by mahammad on 8/26/17.
//

#ifndef DB_IMP_SEMINAR_GRAPHALGO_H
#define DB_IMP_SEMINAR_GRAPHALGO_H

#define VERIFY_ENABLED false

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

    ~GraphAlgo(){
        std::cout<<"Graph Algo delete"<<std::endl;
        delete[] dist;
        delete[] used;
        delete graph;
    }

    void add_edge(int v, std::vector<int>& to, std::vector<int>& weights);

    void add_edge(int from, int to, int weight);

    void finished();

#if VERIFY_ENABLED == false
    void dfs(int v);
    void bfs(int v);
    void dfs_recursion(int v);
#else
    std::vector<int> dfs(int v);
    std::vector<int> bfs(int v);
    void dfs_recursion(int v, std::vector<int>& res);
#endif

    uint64_t dijkstra(int from, int to);
};

#endif //DB_IMP_SEMINAR_GRAPHALGO_H
