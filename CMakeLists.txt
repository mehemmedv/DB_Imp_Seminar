cmake_minimum_required(VERSION 3.7)
project(DB_Imp_Seminar)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-omit-frame-pointer -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")


set(SOURCE_FILES tests/main.cpp src/GraphAlgo.cpp src/ALGraph.cpp src/CSRGraph.cpp src/ALGraphV2.cpp src/CSRGraphV2.cpp)
set(GENERATOR_FILES tests/random_graph_generator.cpp)
set(BENCHMARK_FILES tests/benchmark_test.cpp src/GraphAlgo.cpp src/ALGraph.cpp src/CSRGraph.cpp src/ALGraphV2.cpp src/CSRGraphV2.cpp)
set(GENERATOR_FILESV2 tests/random_graph_generatorv2.cpp)
set(BENCHMARK_FILESV2 tests/benchmark_testv2.cpp src/GraphAlgo.cpp src/ALGraph.cpp src/CSRGraph.cpp src/ALGraphV2.cpp src/CSRGraphV2.cpp)
set(GENERATOR_FILESV3 tests/specific_graph_generator.cpp src/GraphAlgo.cpp src/ALGraph.cpp src/CSRGraph.cpp src/ALGraphV2.cpp src/CSRGraphV2.cpp)


add_executable(DB_Imp_Seminar ${SOURCE_FILES})
add_executable(DB_Generator ${GENERATOR_FILES})
add_executable(DB_Benchmark ${BENCHMARK_FILES})
add_executable(DB_Generatorv2 ${GENERATOR_FILESV2})
add_executable(DB_Benchmarkv2 ${BENCHMARK_FILESV2})
add_executable(DB_Generatorv3 ${GENERATOR_FILESV3})
