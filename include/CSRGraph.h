//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

#include <vector>
#include <iostream>
#include <string.h>
#include <functional>

// 'Compressed sparse row' implementation of Graph
class CSRGraph {

    class EdgeIter {
        class iterator {
        public:
            iterator(uint32_t *ptr, uint32_t *begin_w_ptr) : ptr(ptr), begin_w_ptr(begin_w_ptr) {}

            iterator operator++() {
                ++ptr;
                ++begin_w_ptr;
                return *this;
            }

            bool operator!=(const iterator &other) { return ptr != other.ptr; }

            const std::pair<uint32_t, uint32_t> &operator*() {
                current.first = *ptr;
                current.second = *begin_w_ptr;
                return current;
            };

        private:
            uint32_t *ptr, *begin_w_ptr;
            std::pair<uint32_t, uint32_t > current;
        };

    private:
        uint32_t *begin_ptr, *end_ptr, *begin_w_ptr;
    public:
        EdgeIter(uint32_t *begin_ptr, uint32_t *end_ptr, uint32_t *begin_w_ptr) : begin_ptr(begin_ptr), end_ptr(end_ptr), begin_w_ptr(begin_w_ptr) {}

        iterator begin() const { return iterator(begin_ptr, begin_w_ptr); }

        iterator end() const { return iterator(end_ptr, begin_w_ptr); }
    };

    uint32_t *edges, *offsets;
    uint32_t *weights;
    uint32_t *delta_e;
    uint32_t *delta_w;
    uint64_t cur_idx, v, e;

public:
    EdgeIter get_neighbors(int idx) {
        return EdgeIter(begin(idx), end(idx), begin_weights(idx));
    }

    template <typename CB>
    void applyAllEdges(uint32_t from, CB lambdaCallback) {
        uint32_t *begin_edges = begin(from), *end_edges = end(from), *begin_weights_ptr = begin_weights(from);

        for(; begin_edges != end_edges; ++begin_edges, ++begin_weights_ptr)
            lambdaCallback(*begin_edges, *begin_weights_ptr);
    };

    CSRGraph(uint64_t v, uint64_t e) : v(v), e(e) {
        edges = new uint32_t[e];
        weights = new uint32_t[e];
        offsets = new uint32_t[v + 2];
        memset(offsets, 0, sizeof(uint32_t) * (v + 2));
        //std::cout << v << " " << (offsets[0]) << " " << offsets[1] << " " << offsets[2] << " " << offsets[3] << " " << offsets[4] << std::endl;
        cur_idx = 0;
    }

    ~CSRGraph() {
        delete[] edges;
        delete[] offsets;
        delete[] weights;
        //std::cout<<"CSRGraph delete"<<std::endl;
    }

    void add_edge(int from, std::vector<uint32_t> &to, std::vector<uint32_t> &w);

    inline int get_weight(uint32_t from, uint32_t to, int *ptr) {
        return *ptr;
    }

    void add_edge(int from, int to, int weight = 0);

    void finished();

    void sortByEdgesByNodeId();

    inline uint32_t *begin(int cur_vertex) {
        return &(edges[offsets[cur_vertex]]);
    }

    inline uint32_t *end(int cur_vertex) {
        return &(edges[offsets[cur_vertex + 1]]);
    }

    inline uint32_t *begin_weights(int cur_vertex) {
        return &(weights[offsets[cur_vertex]]);
    }
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
