//
// Created by mahammad on 8/21/17.
//

#include "../include/ALGraph.h"

void ALGraph::add_edge(int from, vector<int>& to) {
    for(int i : to)
        edges[from].push_back(i);
}

void ALGraph::finished() {
    for(int i = 1; i <= v; ++i)
        its[i] = edges[i].begin();
}

bool ALGraph::next_neighbor(int v, int &to) {
    if(its[v] != edges[v].end()){
        to = *(its[v]);
        ++its[v];
        return true;
    }
    return false;
}