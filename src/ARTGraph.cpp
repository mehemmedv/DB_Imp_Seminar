//
// Created by mahammad on 4/10/18.
//
#include "../include/ARTGraph.h"

void ARTGraph::add_edge(int from, std::vector<int> &to, std::vector<int> &w) {
    std::vector<int>::iterator it = w.begin();
    for(int i : to){
        add_edge(from, i, *it);
        ++it;
    }
}

