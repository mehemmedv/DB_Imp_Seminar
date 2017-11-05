//
// Created by mahammad on 11/5/17.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <stdint-gcc.h>
#include <fcntl.h>
#include <unistd.h>

#define maxn 100000

//std::vector<int> edges[maxn + 1];

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
            while (x == i)
                x = rand() % MAXN + 1;
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

    delete[]edges;

    return 0;
}