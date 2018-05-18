//
// Created by mahammad on 11/5/17.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <stdint-gcc.h>
#include <fcntl.h>
#include <unistd.h>
#include <set>

#define maxn 100000

//std::vector<int> edges[maxn + 1];
std::set<int> sset[1001000];
int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::freopen("out.txt", "w", stdout);

    srand(time(NULL));

    int MAXN = std::atoi(argv[1]);
    //std::vector<int> edges;

    int len = std::atoi(argv[2]);

    uint64_t sum = (uint64_t)MAXN * (uint64_t)len;

    int fd = open("out.txt", O_RDWR | O_CREAT, 0666);
    uint64_t offset = 0;
    pwrite(fd, &MAXN, sizeof(int), offset);
    offset += 4;
    pwrite(fd, &sum, sizeof(uint64_t), offset);
    offset += 8;

    int* edges = new int[len];
    int len2 = -1;
    if (argc == 4) {
        len2 = std::atoi(argv[3]);
    }

    for (int i = 1; i <= MAXN; ++i) {

        for (int k = 0; k < len; ++k) {
            // bool flag = false;
            int x;
            //while (!flag) {
            x = rand() % MAXN + 1;
            while (sset[i].find(x) != sset[i].end())
                x = rand() % MAXN + 1;
            sset[i].insert(x);
            edges[k] = x;
        }
        pwrite(fd, &len, sizeof(int), offset);
        offset += 4;
        pwrite(fd, edges, sizeof(int) * len, offset);
        offset = offset + sizeof(int) * len;
        for(int k = 0; k < len; ++k)
            edges[k] = rand() % 100 + 20;
        pwrite(fd, edges, sizeof(int) * len, offset);
        offset = offset + sizeof(int) * len;
    }

    for (int i = 0; i < len2; ++i) {
        int from = i % MAXN + 1;
        int to = rand() % MAXN + 1;
        while (sset[from].find(to) != sset[from].end())
            to = rand() % MAXN + 1;
        sset[from].insert(to);

        int www = rand() % 50 + 1;
        pwrite(fd, &from, sizeof(int), offset);
        offset += 4;
        pwrite(fd, &to, sizeof(int), offset);
        offset += 4;
        pwrite(fd, &www, sizeof(int), offset);
        offset += 4;
        //std::cout <<  << " " << rand() % MAXN + 1 << " " << rand() % 50 + 1 << "\n";
    }

    delete[]edges;

    return 0;
}