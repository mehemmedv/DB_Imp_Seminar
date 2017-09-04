cmake_minimum_required(VERSION 3.7)
project(DB_Imp_Seminar)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES tests/main.cpp src/GraphAlgo.cpp src/ALGraph.cpp src/CSRGraph.cpp)
set(GENERATOR_FILES tests/random_graph_generator.cpp)


add_executable(DB_Imp_Seminar ${SOURCE_FILES})
add_executable(DB_Generator ${GENERATOR_FILES})