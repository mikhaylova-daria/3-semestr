#ifndef DSU_H
#define DSU_H
#include <iostream>
#include <unordered_map>
class DSU {
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

public:
    DSU() {
    }
    void make_set(int i) {
            parent[i] = i;
            rank[i] = 1;
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        } else {
            return parent[x] = find(parent[x]);
        }
    }

    int unite(int x, int y) {
       x = find(x);
       y = find(y);
       if (rank[x] < rank[y]) {
           parent[x] = y;
       } else {
           parent[y] = x;
           if (rank[x] == rank[y]) {
               ++rank[x];
           }
       }
    }
};

#endif // DSU_H
