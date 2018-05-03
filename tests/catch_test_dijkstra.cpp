//
// Created by mahammad on 5/3/18.
//

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/CSRGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/ALGraph.h"
#include "../include/ALGraphV2.h"

TEST_CASE( "Adjacency List Graph Dijkstra test", "[single-file]" ) {
    auto algo = new GraphAlgo<ALGraph>(4, 3);
    algo->add_edge(1, 2, 3);
    algo->add_edge(1, 3, 1);
    algo->add_edge(2, 3, 1);
    REQUIRE(algo->dijkstra(1, 2) == 2);
}

/*

TEST_CASE( "Adjacency List(std::vector) Graph Dijkstra test", "[single-file]" ) {
    auto algo = new GraphAlgo<ALGraphV2>(4, 3);
    algo->add_edge(1, 2, 3);
    algo->add_edge(1, 3, 1);
    algo->add_edge(2, 3, 1);
    REQUIRE(algo->dijkstra(1, 2) == 2);
}

TEST_CASE( "CSR Graph Dijkstra test", "[single-file]" ) {
    auto algo = new GraphAlgo<CSRGraph>(4, 3);
    algo->add_edge(1, 2, 3);
    algo->add_edge(1, 3, 1);
    algo->add_edge(2, 3, 1);
    REQUIRE(algo->dijkstra(1, 2) == 2);
}

 */