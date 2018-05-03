//
// Created by mahammad on 5/3/18.
//

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/GraphAlgo.h"
#include "../include/ALGraph.h"
#include "../include/ALGraphV2.h"
#include "../include/CSRGraph.h"
#include "../include/CSRGraphV2.h"


TEST_CASE( "Adjacency List Graph Dijkstra test", "[single-file]" ) {
    auto algo = new GraphAlgo<ALGraph>(3, 3);
    algo->add_edge(1, 2, 3);
    algo->add_edge(1, 3, 1);
    algo->add_edge(3, 2, 1);
    algo->finished();
    REQUIRE(algo->dijkstra(1, 2) == 2);
    delete algo;
}

TEST_CASE( "Adjacency List(std::vector) Graph Dijkstra test", "[single-file]" ) {
    auto algo = new GraphAlgo<ALGraphV2>(3, 3);
    algo->add_edge(1, 2, 3);
    algo->add_edge(1, 3, 1);
    algo->add_edge(3, 2, 1);
    algo->finished();
    REQUIRE(algo->dijkstra(1, 2) == 2);
    delete algo;
}

TEST_CASE( "CSR Graph Dijkstra test", "[single-file]" ) {
    auto algo = new GraphAlgo<CSRGraph>(4, 3);
    algo->add_edge(1, 2, 3);
    algo->add_edge(1, 3, 1);
    algo->add_edge(3, 2, 1);
    algo->finished();
    REQUIRE(algo->dijkstra(1, 2) == 2);
    delete algo;
}