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

//    graph<char, int> a;
//    a.add_vertex('r');
//    a.add_vertex('s');
//    a.add_vertex('t');
//    a.add_vertex('u');
//    a.add_vertex('v');
//    a.add_vertex('w');
//    a.add_vertex('x');
//    a.add_vertex('y');
//    a.add_edge('v', 'r', 0);
//    a.add_edge('r', 's', 0);
//    a.add_edge('s', 'w', 0);
//    a.add_edge('w', 't', 0);
//    a.add_edge('w', 'x', 0);
//    a.add_edge('x', 't', 0);
//    a.add_edge('t', 'u', 0);
//    a.add_edge('x', 'u', 0);
//    a.add_edge('x', 'y', 0);
//    a.add_edge('y', 'u', 0);
//    a.add_edge('u', 'y', 0);
//    a.add_edge('u', 'x', 0);
//    a.add_edge('y', 'x', 0);
 //   std::list<graph<char, int> > scc = a.Tarjan();
   // std::list<graph<char, int> >::iterator itr_ccs;
//    for (itr_ccs = scc.begin(); itr_ccs != scc.end(); ++itr_ccs) {
//        itr_ccs->print();
//    }
//    a.print();
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

    std::cout << "DFS\n";
    graph<int, int>::iteratorDFS itrDFS;
    for (itrDFS = a.DFSbegin(); itrDFS != a.DFSend(); ++itrDFS) {
        std::cout <<"Вершина:"<< itrDFS->name<<std::endl;
        std::map<std::weak_ptr<vertex<int, int> >, int>::const_iterator itr_adj;
        for (itr_adj = itrDFS->edges_from.cbegin(); itr_adj != itrDFS->edges_from.cend(); ++itr_adj) {
            std::cout << (*itrDFS).name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
        }
    }
//    std::cout << "Псевдо: DFS\n";
//    itrDFS = a.DFSstart();
//    while (itrDFS != a.DFSend()) {
//        std::cout<<itrDFS->name<<" "<<itrDFS.get_color_DFS()<<std::endl;
//        //itrDFS.inc();
//    }

//    graph<char, int>::iteratorBFS itr;
////    for (itr = a.BFSbegin(); itr != a.BFSend(); ++itr) {
////        std::cout <<"Вершина:"<< itr->name<<std::endl;
////        std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
////        for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
////            std::cout << (*itr).name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
////        }
////    }
////    int i = 0;
////    for (itr = a.BFSbegin(); i < 5; ++i, ++itr) {
////        std::cout <<"Вершина:"<< itr->name<<std::endl;
////        std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
////    }
//    std::cout<<"print:\n";
//    a.print();
//    std::cout<<"BFS:\n";
//    for (itr = a.BFSbegin(); itr != a.BFSend(); ++itr) {
//        std::cout <<"Вершина:"<< itr->name<<std::endl;
//        std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
//        for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
//            std::cout << (*itr).name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
//        }
//    }
//    std::cout<<"b:"<<std::endl;
//    graph<char, int> b = a;
//    b.print();
//    std::cout<<"BFS:\n";
//    for (itr = b.BFSbegin(); itr != b.BFSend(); ++itr) {
//        std::cout <<"Вершина:"<< itr->name<<std::endl;
//        std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
//        for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
//            std::cout << (*itr).name<< "-"<<itr_adj->first.lock()->name<<": "<<itr_adj->second<<std::endl;
//        }
//    }


    return 0;
}
