#include "graph.h"

int main() {
        graph<int, int> a;
        a.add_vertex(1);
        a.add_vertex(2);
        a.add_vertex(3);
        a.add_vertex(4);
        a.add_vertex(5);
        a.add_vertex(6);
        a.add_vertex(7);
        a.add_vertex(8);
        a.add_edge(1, 5, 0);
        a.add_edge(6, 5, 0);
        a.add_edge(6, 7, 0);
        a.add_edge(7, 6, 0);
        a.add_edge(6, 2, 0);
        a.add_edge(5, 2, 0);
        a.add_edge(2, 1, 0);
        a.add_edge(3, 2, 0);
        a.add_edge(7, 3, 0);
        a.add_edge(3, 4, 0);
        a.add_edge(4, 3, 0);
        a.add_edge(8, 4, 0);
        a.add_edge(8, 7, 0);
        graph<int, int>::iteratorBFS itr;

////    try {
////        a.remove_vertex('r');
////    } catch (my::exception e) {
////        std::cout<<e.what()<<std::endl;
////    }

////    try {
////        a.remove_edge('s', 'w');
////    } catch (my::exception e) {
////        std::cout<<e.what()<<std::endl;
////    }



//    for (itr = a.BFSbegin(); itr != a.BFSend(); ++itr) {
//        std::cout <<"Вершина:"<< itr->name<<std::endl;
//        std::map<std::weak_ptr<vertex<int, int> >, int>::const_iterator itr_adj;
//        for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
//            std::cout << (*itr).name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
//        }
//    }
//    int i = 0;
//    for (itr = a.BFSbegin(); i < 5; ++i, ++itr) {
//        std::cout <<"Вершина:"<< itr->name<<std::endl;
//        std::map<std::weak_ptr<vertex<int, int> >, int>::const_iterator itr_adj;
//    }
    std::cout<<"print:\n";
    a.print();
    std::cout<<"BFS:\n";
    for (itr = a.BFSbegin(); itr != a.BFSend(); ++itr) {
        std::cout <<"Вершина:"<< itr->name<<std::endl;
        std::map<std::weak_ptr<vertex<int, int> >, int>::const_iterator itr_adj;
        for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
            std::cout << (*itr).name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
        }
    }
    std::cout<<"b:"<<std::endl;
    graph<int, int> b = a;
    b.print();
    std::cout<<"BFS:\n";
    for (itr = b.BFSbegin(); itr != b.BFSend(); ++itr) {
        std::cout <<"Вершина:"<< itr->name<<std::endl;
        std::map<std::weak_ptr<vertex<int, int> >, int>::const_iterator itr_adj;
        for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
            std::cout << (*itr).name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
        }
    }


    return 0;
}
