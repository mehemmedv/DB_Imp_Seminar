//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

#include <vector>
#include <iostream>

// 'Compressed sparse row' implementation of Graph
class CSRGraph {

    class EdgeIter{
        class iterator {
        public:
            iterator(int* ptr): ptr(ptr){}
            iterator operator++() { ++ptr; return *this; }
            bool operator!=(const iterator & other) { return ptr != other.ptr; }
            const int& operator*() const { return *ptr; }
        private:
            int* ptr;
        };
    private:
        int *begin_ptr, *end_ptr;
    public:
        EdgeIter(int* begin_ptr, int* end_ptr) : begin_ptr(begin_ptr), end_ptr(end_ptr) {}
        iterator begin() const { return iterator(begin_ptr); }
        iterator end() const { return iterator(end_ptr); }
    };

    int *edges, *offsets;
    int* weights;
    int *delta_e;
    int *delta_w;
    uint64_t cur_idx, v, e;

public:
    EdgeIter get_neighbors(int idx){
        return EdgeIter(begin(idx), end(idx));
    }

    CSRGraph(uint64_t v, uint64_t e) : v(v), e(e) {
        edges = new int[e];
        offsets = new int[v + 2];
        cur_idx = 0;
        weights = new int[e];
    }

    ~CSRGraph(){
        delete[] edges;
        delete[] offsets;
        delete[] weights;
        //std::cout<<"CSRGraph delete"<<std::endl;
    }

    void add_edge(int from, std::vector<int> &to, std::vector<int>& w);

    int get_weight(uint32_t from, uint32_t to, int* ptr){
        return *ptr;
    }

    void add_edge(int from, int to, int weight = 0);

    void finished();

    void sortByEdgesByNodeId();

    inline int* begin(int cur_vertex){
        return &(edges[offsets[cur_vertex]]);
    }

    inline int* end(int cur_vertex){
        return &(edges[offsets[cur_vertex + 1]]);
    }

    inline int* begin_weights(int cur_vertex){
        return &(weights[offsets[cur_vertex]]);
    }
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
