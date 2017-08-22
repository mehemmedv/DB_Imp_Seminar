//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

// 'Compressed sparse row' implementation of Graph
class CSRGraph {
    int v, e;
    int *edges, *offsets;
public:
    CSRGraph(int v, int e) : v(v), e(e){
        edges = new int[e];
        offsets = new int[v];
    }
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
