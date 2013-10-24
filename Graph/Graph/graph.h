#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <memory>
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <list>

template<typename V, typename E>
class graph;

template <typename V, typename E>
class vertex {
private:
    vertex() {}
public:
    V name;
    std::list<std::pair<std::weak_ptr <vertex<V, E> >, E> > edges_from;
    std::list<std::pair<std::weak_ptr <vertex<V, E> >, E> > edges_to;
    vertex (V  _name): name(_name) {;}
    ~vertex() {}
    friend class graph<V, E>::iteratorBFS;
};



template<typename V, typename E>
class graph
{
    std::unordered_map<V, std::shared_ptr<vertex<V, E> > > vertices;
public:
    class iteratorBFS;
    class iteratorDFS;
    class iteratorBFS_algo;
    graph();
    ~graph();
    std::weak_ptr<vertex<V, E> > add_vertex(V name);
    void add_edge(V vertex_start_name, V vertex_finish_name, E weight);
    iteratorBFS begin();
    iteratorBFS end();

//    void print () const {
//        std::cout<<"name_start - name_finish : weight\n";
//        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
//        for (itr = vertices.cbegin(); itr != vertices.cend(); ++itr) {
//            typename std::list< std::pair<std::weak_ptr<vertex<V, E> >, E > >::const_iterator itr_list;
//          //  std::cout << itr->first << std::endl;
//            for (itr_list = itr->second->edges_from.cbegin(); itr_list != itr->second->edges_from.cend();++itr_list){
//                std::cout <<itr-> first << " - " << (itr_list->first).lock()->name << " : "<<itr_list->second<< std::endl;
//            }
//        }
//        return;
//    }

};

#include "implementation_graph.h"

#include "iterators.h"

#endif // GRAPH_H
