//
// Created by mahammad on 9/26/17.
//

#ifndef DB_IMP_SEMINAR_ALGRAPHV2_H
#define DB_IMP_SEMINAR_ALGRAPHV2_H


#include <list>
#include <vector>

// Adjacency list implementation of Graph
class ALGraphV2{
    int v, e;
    std::vector<int>* edges;
    std::vector<int>* weights;

public:
    ALGraphV2(int v, int e) : v(v), e(e){
        edges = new std::vector<int>[v + 2];
        weights = new std::vector<int>[v + 2];
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
    }

    ~ALGraphV2(){
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
        delete[] edges;
        delete[] weights;
        std::cout<<"ALGraphV2 delete"<<std::endl;
    }

    void add_edge(int from, std::vector<int>& to, std::vector<int>& w);

    void add_edge(int from, int to, int weight = 0);

    void finished();

    void sortByEdgesByNodeId();

    inline std::vector<int>::iterator begin(int cur_vertex) {
        return edges[cur_vertex].begin();
    }

    inline std::vector<int>::iterator end(int cur_vertex){
        return edges[cur_vertex].end();
    }

    inline std::vector<int>::iterator begin_weights(int cur_vertex) {
        return weights[cur_vertex].begin();
    }
};



#endif //DB_IMP_SEMINAR_ALGRAPHV2_H
