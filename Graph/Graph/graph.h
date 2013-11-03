#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <memory>
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace my {

class exception: public std::exception {
private:
    std::string _what;
public:
    exception(const char * _what) throw() {
           this->_what = _what;
    }
    const char* what() const throw(){
        return _what.c_str();
    }
    ~exception() throw(){}
};
}

template<typename V, typename E>
class graph;

template <typename V, typename E>
class vertex {
private:
    vertex() {}
public:
    V name;
    std::map<std::weak_ptr<vertex<V, E> >, E> edges_from;
    std::map<std::weak_ptr<vertex<V, E> >, E> edges_to;
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
    void remove_vertex(V name) throw (my::exception);
    void remove_edge(V vertex_start_name, V vertex_finish_name) throw (my::exception);
    iteratorBFS begin();
    iteratorBFS end();

    void print () const {
        std::cout<<"name_start - name_finish : weight\n";
        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
        for (itr = vertices.cbegin(); itr != vertices.cend(); ++itr) {
            typename std::map<std::weak_ptr<vertex<V, E> >, E>::const_iterator itr_list;
          //  std::cout << itr->first << std::endl;
            for (itr_list = itr->second->edges_from.cbegin(); itr_list != itr->second->edges_from.cend();++itr_list){
                std::cout <<itr-> first << " - " << (itr_list->first).lock()->name << " : "<<itr_list->second<< std::endl;
            }
        }
        return;
    }

};

#include "implementation_graph.h"

#include "iteratorBFS.h"

#endif // GRAPH_H
