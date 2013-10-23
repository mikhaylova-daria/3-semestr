#include "graph.h"
#include "implementation_graph.h"

int main() {
    graph<int, int> a;
    a.add_vertex(1);
    a.add_vertex(2);
    a.add_vertex(3);
    a.add_edge(1, 2, 4);
    a.print();
    return 0;
}
