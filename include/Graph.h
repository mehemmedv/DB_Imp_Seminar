//
// Created by mahammad on 8/26/17.
//

#ifndef DB_IMP_SEMINAR_GRAPH_H
#define DB_IMP_SEMINAR_GRAPH_H


class Graph {
public:
    virtual bool next_neighbor(int v, int& to) = 0;
};


#endif //DB_IMP_SEMINAR_GRAPH_H
