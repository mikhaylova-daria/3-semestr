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

    graph<char, int>::iteratorBFS itr = a.begin();
    for (itr = a.begin(); itr != a.end(); ++itr) {
        std::cout << itr->name<<std::endl;
    }
    // a.print();
    return 0;
}
