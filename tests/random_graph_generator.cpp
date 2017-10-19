//
// Created by mahammad on 8/24/17.
//

#include <iostream>
#include <fstream>
#include <vector>

#define maxn 100000

//std::vector<int> edges[maxn + 1];

int main(int argc, char **argv) {

    std::freopen("out.txt", "w", stdout);

    srand(time(NULL));

    int MAXN = std::atoi(argv[1]);
    std::vector<int> *edges = new std::vector<int>[MAXN + 2];
    int len = std::atoi(argv[2]);
    int len2 = -1;
    if (argc == 4) {
        len2 = std::atoi(argv[3]);
    }

    for (int i = 1; i <= MAXN; ++i) {

        for (int k = edges[i].size() + 1; k <= len; ++k) {
            bool flag = false;
            int x;
            while (!flag) {
                x = rand() % MAXN + 1;
                while (x == i)
                    x = rand() % MAXN + 1;
                for (int j : edges[i])
                    if (j == x) {
                        flag = true;
                        break;
                    }
                if (!flag) {
                    edges[i].push_back(x);
                    edges[x].push_back(i);
                    break;
                }
                flag = false;
            }
        }
    }


    int sum = 0;
    for (int i = 1; i <= MAXN; ++i)
        sum += edges[i].size();

    std::cout << MAXN << " " << sum << std::endl;

    for (int i = 1; i <= MAXN; ++i) {
        std::cout << edges[i].size() << " ";
        for (int j : edges[i])
            std::cout << j << " ";
        std::cout << std::endl;
        for (int j : edges[i])
            std::cout << rand() % 100 + 20 << " ";
        std::cout << std::endl;

    }

    for (int i = 0; i < len2; ++i) {
        std::cout << rand() % MAXN + 1 << " " << rand() % MAXN + 1 << " " <<  rand() % 50 + 1 << std::endl;
    }

    for (int i = 0; i < MAXN + 2; ++i)
        edges[i].clear();
    delete[]edges;

    return 0;
}