//
// Created by mahammad on 12/5/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPHV2_H
#define DB_IMP_SEMINAR_CSRGRAPHV2_H


#include <vector>
#include <iostream>

// 'Compressed sparse row' implementation of Graph
class CSRGraphV2 {
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
    uint64_t cur_idx, v, e;
    uint64_t additional_space = 100;
    uint64_t current_size = 0;

public:
    EdgeIter get_neighbors(int idx){
        return EdgeIter(begin(idx), end(idx));
    }

    CSRGraphV2(uint64_t v, uint64_t e) : v(v), e(e) {
        current_size = e + additional_space;
        edges = new int[current_size];
        offsets = new int[v + 2];
        cur_idx = 0;
        weights = new int[current_size];
    }

    ~CSRGraphV2(){
        delete[] edges;
        delete[] offsets;
        delete[] weights;
        //std::cout<<"CSRGraph delete"<<std::endl;
    }

    int get_weight(uint32_t from, uint32_t to, int* ptr){
        return *ptr;
    }

    void add_edge(int from, std::vector<int> &to, std::vector<int>& w);

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

#endif //DB_IMP_SEMINAR_CSRGRAPHV2_H
