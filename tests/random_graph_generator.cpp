//
// Created by mahammad on 8/24/17.
//

#include <iostream>
#include <fstream>
#include <vector>

#define MAXN 10000

std::vector<int> edges[MAXN];

int main() {

    std::freopen("out.txt", "w", stdout);

    srand(time(NULL));

    for (int i = 1; i <= MAXN; ++i) {

        for (int k = edges[i].size() + 1; k <= 800; ++k) {
            bool flag = false;
            int x;
            while (!flag) {
                x = rand() % MAXN + 1;
                while(x == i)
                    x = rand() % MAXN + 1;
                for (int j : edges[i])
                    if (j == x) {
                        flag = true;
                        break;
                    }
                if(!flag){
                    edges[i].push_back(x);
                    edges[x].push_back(i);
                    break;
                }
                flag = false;
            }
        }


    }
    int sum = 0;
    for(int i = 1; i <= MAXN; ++i)
        sum += edges[i].size();

    std::cout<<MAXN<<" "<<sum<<std::endl;

    for(int i = 1; i <= MAXN; ++i){
        std::cout<<edges[i].size()<<" ";
        for(int j : edges[i])
            std::cout<<j<<" ";
        std::cout<<std::endl;
    }

    return 0;
}