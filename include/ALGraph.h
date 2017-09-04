//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_ALGRAPH_H
#define DB_IMP_SEMINAR_ALGRAPH_H

#include <list>
#include <vector>
#include "Graph.h"

// Adjacency list implementation of Graph
class ALGraph : public Graph{
    int v, e;
    std::list<int>* edges;
    std::list<int>::iterator* its;
public:
    ALGraph(int v, int e) : v(v), e(e){
        std::list<int> x;
        edges = new std::list<int>[v + 2];
        its = new std::list<int>::iterator[v + 2];
        for(int i = 0; i <= v; ++i)
            edges[i].clear();
    }

    class iterator {
    public:
        typedef iterator self_type;
        typedef std::list<int> value_type;
        typedef std::list<int> &reference;
        typedef std::list<int> *pointer;
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

    void add_edge(int v, std::vector<int>& to);

    void finished();

    bool next_neighbor(int v, int& to);

    std::list<int>::iterator begin(int cur_vertex){
        auto it = edges[cur_vertex].begin();
        return it;
    }

    std::list<int>::iterator end(int cur_vertex){
        auto it = edges[cur_vertex].end();
        return it;
    }
};


#endif //DB_IMP_SEMINAR_ALGRAPH_H
