//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

#include <vector>
#include "Graph.h"

// 'Compressed sparse row' implementation of Graph
class CSRGraph : public Graph {
    int *edges, *offsets;
    int cur_idx, v, e;
    int *idx;

public:
    CSRGraph(int v, int e) : v(v), e(e) {
        edges = new int[e];
        offsets = new int[v + 2];
        cur_idx = 0;
        idx = new int[v + 2];
    }

    class iterator {
    public:
        typedef iterator self_type;
        typedef int value_type;
        typedef int &reference;
        typedef int *pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(pointer ptr) : ptr_(ptr) {}

        iterator() : ptr_(nullptr){}

        self_type operator++() {
            self_type i = *this;
            ptr_++;
            return i;
        }

        self_type operator++(int junk) {
            ptr_++;
            return *this;
        }

        reference operator*() { return *ptr_; }

        pointer operator->() { return ptr_; }

        bool operator==(const self_type &rhs) { return ptr_ == rhs.ptr_; }

        bool operator!=(const self_type &rhs) { return ptr_ != rhs.ptr_; }

    private:
        pointer ptr_;
    };

    void add_edge(int v, std::vector<int> &to);

    void finished();

    bool next_neighbor(int v, int &to);

    iterator begin(int cur_vertex){
        iterator it(&(edges[offsets[cur_vertex]]));
        return it;
    }

    iterator end(int cur_vertex){
        iterator it(&(edges[offsets[cur_vertex + 1]]));
        return it;
    }

};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
