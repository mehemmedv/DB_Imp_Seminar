//
// Created by mahammad on 8/21/17.
//

#include "../include/CSRGraph.h"

void CSRGraph::add_edges(int from, int to) {
    if(from != last_vertex)
        offsets[last_vertex] = cur_idx, last_vertex = from;
    edges[cur_idx++] = to;
}

void CSRGraph::set_offset() {
    offsets[v + 1] = cur_idx;
}

