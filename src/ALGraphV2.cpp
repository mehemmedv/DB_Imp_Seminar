//
// Created by mahammad on 9/26/17.
//


#include <iostream>
#include "../include/ALGraphV2.h"

void ALGraphV2::add_edge(int from, std::vector<int>& to, std::vector<int>& w) {
    for(int i : to)
        edges[from].push_back(i);
    for(int i : w)
        weights[from].push_back(i);
}

void ALGraphV2::finished() {
}

std::vector<int>::iterator ALGraphV2::begin(int cur_vertex) {
    return edges[cur_vertex].begin();
}

std::vector<int>::iterator ALGraphV2::end(int cur_vertex){
    return edges[cur_vertex].end();
}

std::vector<int>::iterator ALGraphV2::begin_weights(int cur_vertex) {
    return weights[cur_vertex].begin();
}

void ALGraphV2::add_edge(int from, int to, int weight) {
    edges[from].push_back(to);
    weights[from].push_back(weight);
}