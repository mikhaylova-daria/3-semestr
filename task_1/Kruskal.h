#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "DSU.h"
#include "graph.h"
#include <stdlib.h>
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>

int compare (const void * a, const void * b)
{
  return ( (*(Edge<int>*)a).weight - (*(Edge<int>*)b).weight);
}

class Kruskal {
    DSU dsu;
    Graph<int, int>* g;
    Graph<int, int> f;

public:
    Kruskal(Graph<int, int>* _g): g(_g) {
        std::list<Vetex<int> > vtx = g->get_vetices();
        std::vector<Edge <int> > edg;
        std::list<Vetex<int> >::iterator itr;
        for (itr = vtx.begin(); itr != vtx.end(); ++itr) {
            Vetex<int> v = *itr;
            dsu.make_set(v.id);
            v.list_as_finish.clear();
            v.list_as_start.clear();
            f.add_vtx(v);
            std::list<Edge<int> > edg_v = g->get_edges_inbox(itr->id);
            std::list<Edge<int> >::iterator j;
            for (j = edg_v.begin(); j != edg_v.end(); ++j) {
                edg.push_back(*j);
            }
        }
        std::make_heap (edg.begin(), edg.end());
        std::sort_heap (edg.begin(), edg.end());
            std::vector<Edge<int> >::iterator j;
            for(int j = 0; j != edg.size(); ++j) {
            std::cout<<edg[j].weight<<std::endl;
        }
        for (int i = 0; i < edg.size(); ++i) {
            int u = dsu.find(edg[i].first_v);
            int v = dsu.find(edg[i].second_v);
            if (u != v) {
                dsu.unite(u, v);
                f.add_edg(edg[i]);
            }
        }
        std::cout<<"Kruskal:"<<std::endl;
        std::cout<<f;

    }


};

#endif // KRUSKAL_H
