//
// Created by mahammad on 6/18/18.
//

#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/CSRGraphV2.h"
#include "../include/ARTGraph.h"
#include "../include/ALGraphV2.h"
#include <chrono>
#include <algorithm>
#include <fstream>
#include <functional>
#include "../include/PerfEvent.hpp"

void process_mem_usage(double& vm_usage, double& resident_set)
{
    using std::ios_base;
    using std::ifstream;
    using std::string;

    vm_usage     = 0.0;
    resident_set = 0.0;

    ifstream stat_stream("/proc/self/stat",ios_base::in);

    string pid, comm, state, ppid, pgrp, session, tty_nr;
    string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    string utime, stime, cutime, cstime, priority, nice;
    string O, itrealvalue, starttime;

    unsigned long vsize;
    long rss;

    stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                >> utime >> stime >> cutime >> cstime >> priority >> nice
                >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

    stat_stream.close();

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage     = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}

void print_mem_usage() { // to get memory consumption

    double vm, rss;
    process_mem_usage(vm, rss);
    std::cout <<"RSS: " << rss << std::endl;
}


int main(int argc, char **argv) {
    //freopen("prints.txt", "w", stdout);

    //BenchmarkParameters params;
    //params.setParam("algorithm","applyAllEdges");
    //params.setParam("numEdges",31341600);
    //params.setParam("numNodes",200);

    int node_size = 800;
    int neg_size = 156;
    uint64_t sum = 0;
    auto lambdaFunction = [&sum](uint32_t to, uint32_t weight){
        sum += weight;
    };

/*
    {
        ARTGraph *graph = new ARTGraph(node_size, node_size * neg_size);
        std::vector<uint32_t> temp;
        //for(uint32_t j = 1; j <= sizeee; ++j)
        //    temp.push_back(j);

        for (uint32_t i = 1; i <= node_size; ++i) {
            temp.clear();
            for(uint32_t j = 1; j <= neg_size; ++j)
                temp.push_back(j);

            //for(uint32_t j = 1; j <= sizeee; ++j){
            //    uint32_t to = j;
                //edges[i].push_back(to);

            //for (uint32_t j = 1; j <= neg_size; ++j)
              //  graph->add_edge(i, j, j);
            graph->add_edge(i, temp, temp);

            //}
            //std::cout<<"geldi " << i<<std::endl;
        }
        graph->finished();
        graph->sortByEdgesByNodeId();
        //graph->_print();
        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        uint32_t x, y, cnt = 0;
        //params.setParam("graph","ALV2");
        //PerfEventBlock e(31341600,params);
        //std::cerr << "sudo perf record -g -p " << getpid() << " -e cycles:pp" << std::endl;
        //std::cerr << "Press <Enter> to continue..." << std::endl; std::string str; getline(std::cin,str);


        for(int i = 1; i <= node_size;++ i) {
            graph->applyAllEdges((i % node_size) + 1, lambdaFunction);
            //std::cout<<sum<<std::endl;
            //std::vector<uint32_t> res;
            //for(auto& j : graph->get_neighbors((i % 200) + 1))
            //    x = j.first, y = j.second, ++cnt;
            //  res.push_back(j.first);

            //std::sort(res.begin(), res.end());
            //std::sort(edges[i].begin(), edges[i].end());

            //if (res != edges[i] && res.size() == sizeee)
            //    std::cout << i << " : Different result " << std::endl;
        }
        std::cout<<sum<<std::endl;
        std::cout<<cnt<<std::endl;
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << "Get Neighbors time: " << total_update << std::endl;
    }
    print_mem_usage();
    */

    {
        ARTGraph *graph = new ARTGraph(node_size, node_size * neg_size);
        std::vector<uint32_t> temp;
        std::vector<std::pair<uint32_t, uint32_t>> temp_p;

        //for(uint32_t j = 1; j <= sizeee; ++j)
        //    temp.push_back(j);

        for (uint32_t i = 1; i <= node_size; ++i) {
            temp.clear();
            //for(uint32_t j = i; j <= i + neg_size; ++j)
            //    temp.push_back(j);

            //for(uint32_t j = 1; j <= sizeee; ++j){
            //    uint32_t to = j;
            //edges[i].push_back(to);

            for (uint32_t j = i; j <= i + neg_size; ++j)
              graph->add_edge(i, j, j);

            //graph->add_edge(i, temp, temp);

            //}
            //std::cout<<"geldi " << i<<std::endl;
        }
        graph->finished();
        graph->sortByEdgesByNodeId();
        //graph->_print();
        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        uint32_t x, y, cnt = 0;
        //params.setParam("graph","ALV2");
        //PerfEventBlock e(31341600,params);
        //std::cerr << "sudo perf record -g -p " << getpid() << " -e cycles:pp" << std::endl;
        //std::cerr << "Press <Enter> to continue..." << std::endl; std::string str; getline(std::cin,str);


        for(int i = 1; i <= node_size;++ i) {
            temp_p.clear();

            for(uint32_t j = i; j <= i + neg_size; ++j)
                temp_p.push_back(std::make_pair(j, j));

            auto res = graph->get_neighbors(i);
            std::sort(res.begin(), res.end());
            std::sort(temp_p.begin(), temp_p.end());

            if(res != temp_p){
                std::cout<<"Ferqlidi: "<<i<<std::endl;
            }
            //std::cout<<sum<<std::endl;
            //std::vector<uint32_t> res;
            //for(auto& j : graph->get_neighbors((i % 200) + 1))
            //    x = j.first, y = j.second, ++cnt;
            //  res.push_back(j.first);

            //std::sort(res.begin(), res.end());
            //std::sort(edges[i].begin(), edges[i].end());

            //if (res != edges[i] && res.size() == sizeee)
            //    std::cout << i << " : Different result " << std::endl;
        }
        std::cout<<sum<<std::endl;
        std::cout<<cnt<<std::endl;
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << "Get Neighbors time: " << total_update << std::endl;
    }
    return 0;
}