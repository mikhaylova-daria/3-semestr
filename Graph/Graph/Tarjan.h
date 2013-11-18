#ifndef TARJAN_H
#define TARJAN_H
#include <list>
#include <vector>
template <typename V, typename E>
std::list<graph<V, E> > graph<V, E>::Tarjan() {
    std::vector<std::weak_ptr<vertex<V, E> > > passed_vertices;
    std::unordered_map<V, int> orderDFSid;
    std::weak_ptr<vertex<V, E> > parent_of_current;
    std::list<graph<V, E> > answer;

//    int i = 1;
//    typename graph<V, E>::iteratorDFS itr;
//    parent_of_current = this->vertices.find(this->DFSstart()->name)->second;
//    for (itr = this->DFSstart(); itr != this->DFSend(); itr.inc()) {
//        if (orderDFSid.find(itr->name) == orderDFSid.end()) {
//            orderDFSid.insert(pair<V, int>(itr->name, i));
//            ++i;
//        } else {

//        }


//    int i = 1;
//    typename graph<V, E>::iteratorDFS itr;
//    parent_of_current = this->vertices.find(this->DFSstart()->name)->second;
//    for (itr = this->DFSstart(); itr != this->DFSend(); itr.inc()) {
//        std::cout<<"DFS: "<< itr->name;
//        if (itr.get_color_DFS() == 1) {
//        //    std::cout<<"&"<<std::endl;
//            passed_vertices.push_back(this->vertices.find(itr->name)->second);
//            orderDFSid.push_back(i);
//            itr->set_alg_color(i);
//            ++i;
//        }
//        if (itr.get_color_DFS() == 2) {
//           // std::cout<<"*"<<std::endl;
//            std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
//            for (itr_adj = itr->edges_from.cbegin(); itr_adj != itr->edges_from.cend(); ++itr_adj) {
//                if (itr->get_alg_color() > itr_adj->first.lock()->get_alg_color()) {
//                    itr->set_alg_color(itr_adj->first.lock()->get_alg_color());
//                    std::cout<<"$"<<std::endl;
//                }
//            }
//            graph<V, E> local_comp;
//            std::weak_ptr<vertex<V, E> > vtx;
//            vtx = passed_vertices.back();
//            orderDFSid.pop_back();
//            local_comp.add_vertex(vtx.lock()->name);
//            int id;
//            do {
//                //std::cout<<(vtx.lock())<<std::endl;
//                vtx = passed_vertices.back();
//                std::cout<<vtx.lock()->name<<std::endl;
//                passed_vertices.pop_back();
//                if (vtx.lock()->get_alg_color() > itr->get_alg_color()) {
//                    std::cout<<itr->get_alg_color()<<std::endl;
//                    vtx.lock()->set_alg_color(itr->get_alg_color());
//                }
//                id = orderDFSid.back();
//                //std::cout<<id<<std::endl;
//                orderDFSid.pop_back();
//                local_comp.add_vertex(vtx.lock()->name);
//                //добавление рёбер компоненты
////                std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
////                for (itr_adj = vtx.lock()->edges_from.cbegin(); itr_adj != vtx.lock()->edges_from.cend(); ++itr_adj) {
////                    if (local_comp.vertices.find(itr_adj->first.lock()->name) != local_comp.vertices.end()) {
////                        local_comp.add_edge(vtx.lock()->name, itr_adj->first.lock()->name, itr_adj->second);
////                    }
////                }
////                for (itr_adj = vtx.lock()->edges_to.cbegin(); itr_adj != vtx.lock()->edges_to.cend(); ++itr_adj) {
////                    if (local_comp.vertices.find(itr_adj->first.lock()->name) != local_comp.vertices.end()) {
////                        local_comp.add_edge(itr_adj->first.lock()->name, itr_adj->second, vtx.lock()->name);
////                    }
////                }
//            } while (vtx.lock()->get_alg_color() != id);
//             local_comp.print();
//            answer.push_back(local_comp);
//        }
//    }
    return answer;

}

#endif // TARJAN_H
