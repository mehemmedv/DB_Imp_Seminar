//
// Created by mahammad on 11/5/17.
//

#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/ALGraphV2.h"
#include "../include/CSRGraphV2.h"
#include "../include/ARTGraph.h"
#include <chrono>
#include <memory>
#include <stdint-gcc.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>


#define CMP_DFS_ENABLED true // compare dfs latencies
#define CMP_BFS_ENABLED true // compare bfs latencies
#define CMP_DIJIKSTRA_ENABLED true // compare dijikstra latencies

std::vector<int> edges;
std::vector<int> weights;

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

    std::string type = argv[1];
    std::string algo_type = argv[2];
    std::string sorted = argv[3];

    //freopen("out.txt", "r", stdin);
    int v, ssize, to;
    uint64_t e;

    int fd = open("out.txt", O_RDWR | O_CREAT, 0666);
    uint64_t offset = 0;
    pread(fd, &v, sizeof(int), offset);
    offset += 4;
    pread(fd, &e, sizeof(uint64_t), offset);
    offset += 8;

    //std::cin >> v >> e;

    if (type == "-CSR") { // CSR
        auto algo = new GraphAlgo<CSRGraph>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            //std::cin >> ssize;
            pread(fd, &ssize, sizeof(int), offset);
            offset += 4;

            int *temp = new int[ssize];

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;

            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                edges.push_back(temp[j]);
            }

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;


            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                weights.push_back(temp[j]);
            }
            algo->add_edge(i + 1, edges, weights);
            delete[]temp;
        }
        algo->finished();

        int cnt_rounds = -1;
        int x = -1;
        cnt_rounds = std::atoi(argv[4]);
        if (sorted == "sorted")
            algo->sortByEdgesByNodeId();
        else if (sorted == "mixed") {
            x = std::atoi(argv[5]);
        }

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph DFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->bfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph BFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dijkstra(1, (i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph Dijkstra time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        }
        print_mem_usage();

        delete algo;
    } else if (type == "-CSRV2") { // CSR
        auto algo = new GraphAlgo<CSRGraphV2>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            //std::cin >> ssize;
            pread(fd, &ssize, sizeof(int), offset);
            offset += 4;

            int *temp = new int[ssize];

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;

            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                edges.push_back(temp[j]);
            }

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;


            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                weights.push_back(temp[j]);
            }
            algo->add_edge(i + 1, edges, weights);
            delete[]temp;
        }
        algo->finished();

        int cnt_rounds = -1;
        int x = -1;
        cnt_rounds = std::atoi(argv[4]);
        if (sorted == "sorted")
            algo->sortByEdgesByNodeId();
        else if (sorted == "mixed") {
            x = std::atoi(argv[5]);
        }

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph DFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->bfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph BFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dijkstra(1, (i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph Dijkstra time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        }
        print_mem_usage();

        delete algo;
    } else if (type == "-AL") { // ALGraph
        auto algo = new GraphAlgo<ALGraph>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            //std::cin >> ssize;
            pread(fd, &ssize, sizeof(int), offset);
            offset += 4;

            int *temp = new int[ssize];

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;

            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                edges.push_back(temp[j]);
            }

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;


            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                weights.push_back(temp[j]);
            }
            algo->add_edge(i + 1, edges, weights);
            delete[]temp;
        }
        algo->finished();

        int cnt_rounds = -1;
        int x = -1;
        cnt_rounds = std::atoi(argv[4]);

        if (sorted == "sorted")
            algo->sortByEdgesByNodeId();
        else if (sorted == "mixed") {
            x = std::atoi(argv[5]);
        }

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"ALGraph Graph DFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->bfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"ALGraph Graph BFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dijkstra(1, (i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"ALGraph Graph Dijkstra time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        }
        print_mem_usage();
        delete algo;
    } else if(type == "ALV2") { // ALGraphV2
        auto algo = new GraphAlgo<ALGraphV2>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            //std::cin >> ssize;
            pread(fd, &ssize, sizeof(int), offset);
            offset += 4;

            int *temp = new int[ssize];

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;

            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                edges.push_back(temp[j]);
            }

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;


            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                weights.push_back(temp[j]);
            }
            algo->add_edge(i + 1, edges, weights);
            delete[]temp;
        }
        algo->finished();

        int cnt_rounds = -1;
        int x = -1;
        cnt_rounds = std::atoi(argv[4]);

        if (sorted == "sorted")
            algo->sortByEdgesByNodeId();
        else if (sorted == "mixed") {
            x = std::atoi(argv[5]);
        }

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;

//                    std::cin>>fr_v>>to_v>>w_v;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"ALGraphV2 Graph DFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0) {
                    sum += algo->bfs((i - 1) % v + 1);
                } else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;

                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"ALGraphV2 Graph BFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dijkstra(1, (i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"ALGraphV2 Graph Dijkstra time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        }
        print_mem_usage();
        delete algo;
    } else { // ARTGraph
        auto algo = new GraphAlgo<ARTGraph>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            //std::cin >> ssize;
            pread(fd, &ssize, sizeof(int), offset);
            offset += 4;

            int *temp = new int[ssize];

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;

            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                edges.push_back(temp[j]);
            }

            pread(fd, temp, sizeof(int) * ssize, offset);
            offset = offset + sizeof(int) * ssize;


            for (int j = 0; j < ssize; ++j) {
                //std::cin >> to;
                weights.push_back(temp[j]);
            }
            algo->add_edge(i + 1, edges, weights);
            delete[]temp;
        }
        algo->finished();

        int cnt_rounds = -1;
        int x = -1;
        cnt_rounds = std::atoi(argv[4]);
        if (sorted == "sorted")
            algo->sortByEdgesByNodeId();
        else if (sorted == "mixed") {
            x = std::atoi(argv[5]);
        }

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph DFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->bfs((i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph BFS time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            auto total_update = 0LL;
            int cnt_updates = 0;
            for (int i = 1; i <= cnt_rounds; ++i) {
                if (x == -1 || i % x != 0)
                    sum += algo->dijkstra(1, (i - 1) % v + 1);
                else {
                    int fr_v, to_v, w_v;
                    pread(fd, &fr_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &to_v, sizeof(int), offset);
                    offset += 4;
                    pread(fd, &w_v, sizeof(int), offset);
                    offset += 4;
                    ++cnt_updates;
                    auto begin_update = std::chrono::high_resolution_clock::now();
                    algo->add_edge(fr_v, to_v, w_v);
                    auto end_update = std::chrono::high_resolution_clock::now();
                    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //std::cout<<"sum: "<<sum<<std::endl;
            //std::cout<<"CSR Graph Dijkstra time: "<<passed.count()<<std::endl;
            std::cout << type << " " << algo_type << " " << sorted << " " << cnt_rounds << " " << x << "   nodes = "
                      << v << "  time:  " << passed.count() << std::endl;
            std::cout<<"Average update time: "<<total_update * 1.0 / (cnt_updates*1.0)<<std::endl;
        }
        print_mem_usage();

        delete algo;
    }
    return 0;
}