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
#include "../include/ARTGraph.h"


TEST_CASE("Adjacency List Graph Dijkstra test", "[single-file]") {
    auto algo = new GraphAlgo<ALGraph>(5, 0);
    algo->add_edge(1, 2, 2);
    algo->add_edge(2, 3, 4);
    algo->add_edge(1, 4, 1);
    algo->add_edge(5, 3, 1);
    algo->add_edge(4, 3, 3);
    algo->add_edge(3, 5, 1);
    algo->add_edge(4, 5, 1);
    algo->add_edge(3, 1, 10);
    algo->finished();

    REQUIRE(algo->dijkstra(1, 2) == 2);
    REQUIRE(algo->dijkstra(1, 3) == 3);
    REQUIRE(algo->dijkstra(1, 4) == 1);
    REQUIRE(algo->dijkstra(1, 5) == 2);

    REQUIRE(algo->dijkstra(2, 1) == 14);
    REQUIRE(algo->dijkstra(2, 3) == 4);
    REQUIRE(algo->dijkstra(2, 4) == 15);
    REQUIRE(algo->dijkstra(2, 5) == 5);

    REQUIRE(algo->dijkstra(3, 1) == 10);
    REQUIRE(algo->dijkstra(3, 2) == 12);
    REQUIRE(algo->dijkstra(3, 4) == 11);
    REQUIRE(algo->dijkstra(3, 5) == 1);

    REQUIRE(algo->dijkstra(4, 1) == 12);
    REQUIRE(algo->dijkstra(4, 2) == 14);
    REQUIRE(algo->dijkstra(4, 3) == 2);
    REQUIRE(algo->dijkstra(4, 5) == 1);

    REQUIRE(algo->dijkstra(5, 1) == 11);
    REQUIRE(algo->dijkstra(5, 2) == 13);
    REQUIRE(algo->dijkstra(5, 3) == 1);
    REQUIRE(algo->dijkstra(5, 4) == 12);

    delete algo;
}

TEST_CASE("Adjacency List(std::vector) Graph Dijkstra test", "[single-file]") {
    auto algo = new GraphAlgo<ALGraphV2>(5, 0);
    algo->add_edge(1, 2, 2);
    algo->add_edge(2, 3, 4);
    algo->add_edge(1, 4, 1);
    algo->add_edge(5, 3, 1);
    algo->add_edge(4, 3, 3);
    algo->add_edge(3, 5, 1);
    algo->add_edge(4, 5, 1);
    algo->add_edge(3, 1, 10);
    algo->finished();

    REQUIRE(algo->dijkstra(1, 2) == 2);
    REQUIRE(algo->dijkstra(1, 3) == 3);
    REQUIRE(algo->dijkstra(1, 4) == 1);
    REQUIRE(algo->dijkstra(1, 5) == 2);

    REQUIRE(algo->dijkstra(2, 1) == 14);
    REQUIRE(algo->dijkstra(2, 3) == 4);
    REQUIRE(algo->dijkstra(2, 4) == 15);
    REQUIRE(algo->dijkstra(2, 5) == 5);

    REQUIRE(algo->dijkstra(3, 1) == 10);
    REQUIRE(algo->dijkstra(3, 2) == 12);
    REQUIRE(algo->dijkstra(3, 4) == 11);
    REQUIRE(algo->dijkstra(3, 5) == 1);

    REQUIRE(algo->dijkstra(4, 1) == 12);
    REQUIRE(algo->dijkstra(4, 2) == 14);
    REQUIRE(algo->dijkstra(4, 3) == 2);
    REQUIRE(algo->dijkstra(4, 5) == 1);

    REQUIRE(algo->dijkstra(5, 1) == 11);
    REQUIRE(algo->dijkstra(5, 2) == 13);
    REQUIRE(algo->dijkstra(5, 3) == 1);
    REQUIRE(algo->dijkstra(5, 4) == 12);
    delete algo;
}

TEST_CASE("CSR Graph Dijkstra test", "[single-file]") {
    auto algo = new GraphAlgo<CSRGraph>(5, 0);
    algo->add_edge(1, 2, 2);
    algo->add_edge(2, 3, 4);
    algo->add_edge(1, 4, 1);
    algo->add_edge(5, 3, 1);
    algo->add_edge(4, 3, 3);
    algo->add_edge(3, 5, 1);
    algo->add_edge(4, 5, 1);
    algo->add_edge(3, 1, 10);
    algo->finished();

    REQUIRE(algo->dijkstra(1, 2) == 2);
    REQUIRE(algo->dijkstra(1, 3) == 3);
    REQUIRE(algo->dijkstra(1, 4) == 1);
    REQUIRE(algo->dijkstra(1, 5) == 2);

    REQUIRE(algo->dijkstra(2, 1) == 14);
    REQUIRE(algo->dijkstra(2, 3) == 4);
    REQUIRE(algo->dijkstra(2, 4) == 15);
    REQUIRE(algo->dijkstra(2, 5) == 5);

    REQUIRE(algo->dijkstra(3, 1) == 10);
    REQUIRE(algo->dijkstra(3, 2) == 12);
    REQUIRE(algo->dijkstra(3, 4) == 11);
    REQUIRE(algo->dijkstra(3, 5) == 1);

    REQUIRE(algo->dijkstra(4, 1) == 12);
    REQUIRE(algo->dijkstra(4, 2) == 14);
    REQUIRE(algo->dijkstra(4, 3) == 2);
    REQUIRE(algo->dijkstra(4, 5) == 1);

    REQUIRE(algo->dijkstra(5, 1) == 11);
    REQUIRE(algo->dijkstra(5, 2) == 13);
    REQUIRE(algo->dijkstra(5, 3) == 1);
    REQUIRE(algo->dijkstra(5, 4) == 12);
    delete algo;
}

TEST_CASE("CSR GraphV2 Dijkstra test", "[single-file]") {
    auto algo = new GraphAlgo<CSRGraphV2>(5, 0);
    algo->add_edge(1, 2, 2);
    algo->add_edge(2, 3, 4);
    algo->add_edge(1, 4, 1);
    algo->add_edge(5, 3, 1);
    algo->add_edge(4, 3, 3);
    algo->add_edge(3, 5, 1);
    algo->add_edge(4, 5, 1);
    algo->add_edge(3, 1, 10);
    algo->finished();

    REQUIRE(algo->dijkstra(1, 2) == 2);
    REQUIRE(algo->dijkstra(1, 3) == 3);
    REQUIRE(algo->dijkstra(1, 4) == 1);
    REQUIRE(algo->dijkstra(1, 5) == 2);

    REQUIRE(algo->dijkstra(2, 1) == 14);
    REQUIRE(algo->dijkstra(2, 3) == 4);
    REQUIRE(algo->dijkstra(2, 4) == 15);
    REQUIRE(algo->dijkstra(2, 5) == 5);

    REQUIRE(algo->dijkstra(3, 1) == 10);
    REQUIRE(algo->dijkstra(3, 2) == 12);
    REQUIRE(algo->dijkstra(3, 4) == 11);
    REQUIRE(algo->dijkstra(3, 5) == 1);

    REQUIRE(algo->dijkstra(4, 1) == 12);
    REQUIRE(algo->dijkstra(4, 2) == 14);
    REQUIRE(algo->dijkstra(4, 3) == 2);
    REQUIRE(algo->dijkstra(4, 5) == 1);

    REQUIRE(algo->dijkstra(5, 1) == 11);
    REQUIRE(algo->dijkstra(5, 2) == 13);
    REQUIRE(algo->dijkstra(5, 3) == 1);
    REQUIRE(algo->dijkstra(5, 4) == 12);
    delete algo;
}


TEST_CASE("ART Graph Dijkstra test", "[single-file]") {
    auto algo = new GraphAlgo<ARTGraph>(5, 0);
    algo->add_edge(1, 2, 2);
    algo->add_edge(2, 3, 4);
    algo->add_edge(1, 4, 1);
    algo->add_edge(5, 3, 1);
    algo->add_edge(4, 3, 3);
    algo->add_edge(3, 5, 1);
    algo->add_edge(4, 5, 1);
    algo->add_edge(3, 1, 10);
    algo->finished();

    REQUIRE(algo->dijkstra(1, 2) == 2);
    REQUIRE(algo->dijkstra(1, 3) == 3);
    REQUIRE(algo->dijkstra(1, 4) == 1);
    REQUIRE(algo->dijkstra(1, 5) == 2);

    REQUIRE(algo->dijkstra(2, 1) == 14);
    REQUIRE(algo->dijkstra(2, 3) == 4);
    REQUIRE(algo->dijkstra(2, 4) == 15);
    REQUIRE(algo->dijkstra(2, 5) == 5);

    REQUIRE(algo->dijkstra(3, 1) == 10);
    REQUIRE(algo->dijkstra(3, 2) == 12);
    REQUIRE(algo->dijkstra(3, 4) == 11);
    REQUIRE(algo->dijkstra(3, 5) == 1);

    REQUIRE(algo->dijkstra(4, 1) == 12);
    REQUIRE(algo->dijkstra(4, 2) == 14);
    REQUIRE(algo->dijkstra(4, 3) == 2);
    REQUIRE(algo->dijkstra(4, 5) == 1);

    REQUIRE(algo->dijkstra(5, 1) == 11);
    REQUIRE(algo->dijkstra(5, 2) == 13);
    REQUIRE(algo->dijkstra(5, 3) == 1);
    REQUIRE(algo->dijkstra(5, 4) == 12);

}