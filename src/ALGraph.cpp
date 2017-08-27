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