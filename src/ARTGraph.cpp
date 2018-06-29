//
// Created by mahammad on 4/10/18.
//
#include "../include/ARTGraph.h"

void ARTGraph::add_edge(uint32_t from, std::vector<uint32_t> &to, std::vector<uint32_t> &w) {
    std::vector<uint32_t>::iterator it = w.begin();
    int cnt = 0;
    for(uint32_t i : to){
        add_edge(from, i, *it);
        ++it;
        std::cout<<"done: "<<++cnt<<std::endl;
    }
}