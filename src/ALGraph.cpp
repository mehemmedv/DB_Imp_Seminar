//
// Created by mahammad on 8/21/17.
//

#include <iostream>
#include "../include/ALGraph.h"

void ALGraph::add_edge(int from, std::vector<int>& to) {
    for(int i : to)
        edges[from].push_back(i);
}

void ALGraph::finished() {
    for(int i = 1; i <= v; ++i)
        its[i] = edges[i].begin();
}

bool ALGraph::next_neighbor(int from, int &to) {
    if(its[from] != edges[from].end()){
        to = *(its[from]);
        ++its[from];
        return true;
    }
    return false;
}

std::list<int>::iterator ALGraph::begin(int cur_vertex) {
    return edges[cur_vertex].begin();
}

std::list<int>::iterator ALGraph::end(int cur_vertex){
    return edges[cur_vertex].end();
}

std::list<int>::iterator ALGraph::begin_weights(int cur_vertex) {
    return weights[cur_vertex].begin();
}

void ALGraph::add_edge(int from, int to, int weight) {
    edges[from].push_back(to);
}