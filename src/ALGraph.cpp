//
// Created by mahammad on 8/21/17.
//

#include <iostream>
#include "../include/ALGraph.h"

void ALGraph::add_edge(int from, std::vector<int>& to, std::vector<int>& w) {
    for(int i : to)
        edges[from].push_back(i);
    for(int i : w)
        weights[from].push_back(i);
}

void ALGraph::finished() {
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
    weights[from].push_back(weight);
}