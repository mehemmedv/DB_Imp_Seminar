//
// Created by mahammad on 9/26/17.
//

#ifndef DB_IMP_SEMINAR_ALGRAPHV2_H
#define DB_IMP_SEMINAR_ALGRAPHV2_H


#include <list>
#include <vector>
#include <functional>

// Adjacency list implementation of Graph
class ALGraphV2{
    class EdgeIter {
        class iterator {
        public:
            iterator(std::vector<uint32_t>::iterator ptr, std::vector<uint32_t>::iterator begin_w_ptr) : ptr(ptr), begin_w_ptr(begin_w_ptr) {}

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
            std::vector<uint32_t>::iterator ptr, begin_w_ptr;
            std::pair<uint32_t, uint32_t > current;
        };

    private:
        std::vector<uint32_t>::iterator begin_ptr, end_ptr, begin_w_ptr;
    public:
        EdgeIter(std::vector<uint32_t>::iterator begin_ptr, std::vector<uint32_t>::iterator end_ptr, std::vector<uint32_t>::iterator begin_w_ptr) : begin_ptr(begin_ptr), end_ptr(end_ptr), begin_w_ptr(begin_w_ptr) {}

        iterator begin() const { return iterator(begin_ptr, begin_w_ptr); }

        iterator end() const { return iterator(end_ptr, begin_w_ptr); }
    };

    uint64_t v, e;
    std::vector<uint32_t>* edges;
    std::vector<uint32_t>* weights;

public:

    EdgeIter get_neighbors(int idx){
        return EdgeIter(begin(idx), end(idx), begin_weights(idx));
        //return edges[idx];
    }

    ALGraphV2(uint64_t v, uint64_t e) : v(v), e(e){
        edges = new std::vector<uint32_t >[v + 2];
        weights = new std::vector<uint32_t>[v + 2];
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
    }

    ~ALGraphV2(){
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
        delete[] edges;
        delete[] weights;
        //std::cout<<"ALGraphV2 delete"<<std::endl;
    }

    template <typename CB>
    void applyAllEdges(uint32_t from, CB lambdaCallback){
        std::vector<uint32_t>::iterator begin_edges, end_edges, begin_weights_ptr;
        begin_edges = begin(from);
        end_edges = end(from);
        begin_weights_ptr = begin_weights(from);

        for(; begin_edges != end_edges; ++begin_edges, ++begin_weights_ptr)
            lambdaCallback(*begin_edges, *begin_weights_ptr);
    };

    void add_edge(int from, std::vector<uint32_t >& to, std::vector<uint32_t>& w);

    void add_edge(uint32_t from, uint32_t to, uint32_t weight = 0);

    void finished();

    void sortByEdgesByNodeId();

    inline std::vector<uint32_t>::iterator begin(int cur_vertex) {
        return edges[cur_vertex].begin();
    }

    inline std::vector<uint32_t>::iterator end(int cur_vertex){
        return edges[cur_vertex].end();
    }

    inline std::vector<uint32_t>::iterator begin_weights(int cur_vertex) {
        return weights[cur_vertex].begin();
    }
};



#endif //DB_IMP_SEMINAR_ALGRAPHV2_H
