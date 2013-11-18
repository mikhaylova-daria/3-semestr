#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <list>
#include <memory>
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

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

template <typename T>
bool operator < (std::weak_ptr<T> ptr, std::weak_ptr<T> other_ptr){
    return ptr.lock().get() < other_ptr.lock().get();
}

template <typename T>
bool operator == (const std::weak_ptr<T> & ptr, const std::weak_ptr<T> & other_ptr){
    return ptr.lock().get() == other_ptr.lock().get();
}


template<typename V, typename E>
class graph;

template <typename V, typename E>
class vertex {
private:
    vertex() {}
    int alg_color = 0;
public:
    V name;
    std::map<std::weak_ptr<vertex<V, E> >, E> edges_from;
    std::map<std::weak_ptr<vertex<V, E> >, E> edges_to;
    vertex (V  _name): name(_name) {;}
    ~vertex() {}
    void set_alg_color(int color){
        alg_color = color;
    }
    int get_alg_color(){
        return alg_color;
    }
    friend class graph<V, E>::iteratorBFS;
    friend class graph<V, E>;
};



template<typename V, typename E>
class graph
{
public:
    class iteratorBFS;
    class iteratorDFS;
    graph();
    ~graph();
    std::weak_ptr<vertex<V, E> > add_vertex(V name);
    void add_edge(V vertex_start_name, V vertex_finish_name, E weight);
    void remove_vertex(V name) throw (my::exception);
    void remove_edge(V vertex_start_name, V vertex_finish_name) throw (my::exception);
    iteratorBFS BFSbegin();
    iteratorBFS BFSend();
    iteratorDFS DFSbegin();
    iteratorDFS DFSbegin(V start);
    iteratorDFS DFSend();
    iteratorDFS DFSstart();
    iteratorDFS DFSstart(V start);
    void clear();
    graph<V, E>& operator =(graph<V, E>& other);
    void print () const {
        std::cout<<"name_start - name_finish : weight\n";
        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
        for (itr = vertices.cbegin(); itr != vertices.cend(); ++itr) {
            typename std::map<std::weak_ptr<vertex<V, E> >, E>::const_iterator itr_list;
            std::cout << itr->first << std::endl;
            for (itr_list = itr->second->edges_from.cbegin(); itr_list != itr->second->edges_from.cend();++itr_list){
                std::cout <<itr-> first << " - " << (itr_list->first).lock()->name << " : "<<itr_list->second<< std::endl;
            }
        }
        return;
    }
private:
    std::unordered_map<V, std::shared_ptr<vertex<V, E> > > vertices;
    std::shared_ptr<vertex<V, E> > my_null;
    iteratorBFS end_itr_BFS;
    iteratorDFS end_itr_DFS;
public:
    std::list<graph<V, E> > Tarjan();
};

#include "iteratorBFS.h"
#include "iteratorDFS.h"
#include "implementation_graph.h"
#include "Tarjan.h"
#endif // GRAPH_H
