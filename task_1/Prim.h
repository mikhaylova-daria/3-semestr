#ifndef PRIM_H
#define PRIM_H
#include "DSU.h"
#include "graph.h"
#include <map>
#include <limits>
#include <unordered_map>

struct Comp {
    Comp(){;}
    bool operator() (const std::pair<int, int>& f, const std::pair<int, int>& s) {
        return f.second < s.second;
    }
};


class Prim {
    std::set<std::pair<int, int> >  q; //номер вершины - значение ключа
    std::set<int> q_ident;//характерист. мн.-во q
    Graph<int, int>* g;
    std::vector<int> key;
    std::vector<int> parent;
public:
    Prim(Graph<int, int> * _g):g(_g) {
        std::list<Vetex<int> > vtx =g->get_vetices();
        std::list<Vetex<int> >::iterator itr_vtx;
        itr_vtx = vtx.begin();
        q.insert(std::pair<int, int>(std::pair<int, int>(itr_vtx->id, 0)));
        q_ident.insert(itr_vtx->id);
        key.push_back(0);
        parent.push_back(0);
        ++itr_vtx;
        for (; itr_vtx != vtx.end(); ++itr_vtx) {
            q.insert(std::pair<int, int> (itr_vtx->id, std::numeric_limits<int>::max()));
            q_ident.insert(itr_vtx->id);
            key.push_back(std::numeric_limits<int>::max());
            parent.push_back(0);
        }
        while (!q.empty()) {
            int u = q.begin()->first;
            q.erase(q.begin());
            q_ident.erase(u);
            std::list<Edge<int> > adj = g->get_edges_outbox(u);
            std::list<Edge<int> >::iterator itr;
            for (itr = adj.begin(); itr != adj.end(); ++itr) {
                if (q_ident.find(itr->second_v) != q_ident.end() && itr->weight < key[itr->second_v - 1]) {
                    q.erase(std::pair<int, int>(itr->second_v, key[itr->second_v - 1]));
                    q.insert(std::pair<int, int> (itr->second_v, itr->weight));
                    key[itr->second_v - 1] = itr->weight;
                    parent[itr->second_v - 1] = u;
                }
            }
            adj = g->get_edges_inbox(u);
            for (itr = adj.begin(); itr != adj.end(); ++itr) {
                if (q_ident.find(itr->first_v) != q_ident.end() && itr->weight < key[itr->first_v - 1]) {
                    q.erase(std::pair<int, int>(itr->first_v, key[itr->first_v - 1]));
                    q.insert(std::pair<int, int> (itr->first_v, itr->weight));
                    key[itr->first_v - 1] = itr->weight;
                    parent[itr->first_v - 1] = u;
                }
            }
        }
        std::cout<<"Prim:"<<std::endl;
        for (int i = 0; i < parent.size(); ++i) {
            if (parent[i] > 0) {
                std::cout << i + 1 << " " << parent[i]<<std::endl;
            }
        }
    }

};

#endif // PRIM_H
