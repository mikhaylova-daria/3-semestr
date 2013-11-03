#include "graph.h"

int main() {
    graph<char, int> a;
    a.add_vertex('r');
    a.add_vertex('s');
    a.add_vertex('t');
    a.add_vertex('u');
    a.add_vertex('v');
    a.add_vertex('w');
    a.add_vertex('x');
    a.add_vertex('y');
    a.add_edge('v', 'r', 0);
    a.add_edge('r', 's', 0);
    a.add_edge('s', 'w', 0);
    a.add_edge('w', 't', 0);
    a.add_edge('w', 'x', 0);
    a.add_edge('x', 't', 0);
    a.add_edge('t', 'u', 0);
    a.add_edge('x', 'u', 0);
    a.add_edge('x', 'y', 0);
    a.add_edge('y', 'u', 0);
    try {
        a.remove_vertex('r');
    } catch (my::exception e) {
        std::cout<<e.what()<<std::endl;
    }

    try {
        a.remove_edge('s', 'w');
    } catch (my::exception e) {
        std::cout<<e.what()<<std::endl;
    }
    a.print();
    graph<char, int>::iteratorBFS itr;
    for (itr = a.begin(); itr != a.end(); ++itr) {
        std::cout <<"Вершина:"<< itr->name<<std::endl;
        std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
        for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
            std::cout << itr->name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
        }
    }

    return 0;
}
