//
// Created by mahammad on 8/21/17.
//

#include "../include/ALGraph.h"

void ALGraph::add_edge(int from, int to) {
    edges[from].push_front(to);
}