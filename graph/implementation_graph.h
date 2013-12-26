#ifndef IMPLEMENTATION_GRAPH_H
#define IMPLEMENTATION_GRAPH_H

#include <queue>

template <typename V, typename E>
graph<V, E>::graph() {
    my_null = std::shared_ptr<vertex<V, E> >(new vertex<V, E>());
    end_itr_BFS.current = this->my_null;
}

template <typename V, typename E>
graph<V, E>::~graph() {
}

template <typename V, typename E>
std::weak_ptr<vertex<V, E> > graph<V,E>::add_vertex(V name) {
    std::weak_ptr<vertex<V, E> > adding_vertex_ptr;
    typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::iterator finding_itr;
    finding_itr = this->vertices.find(name);
    if (finding_itr == this->vertices.end()) {
        std::shared_ptr<vertex<V, E> > v_ptr(new vertex<V, E>(name));
        std::pair<V, std::shared_ptr<vertex<V, E> > > inserting;
        inserting.first = name;
        inserting.second = v_ptr;
        adding_vertex_ptr = this->vertices.insert(inserting).first->second;
    } else {
        adding_vertex_ptr = finding_itr->second;
    }
    return adding_vertex_ptr;
}

template <typename V, typename E>
void graph<V, E>::add_edge(V vertex_start_name, V vertex_finish_name, E weight) {
    std::weak_ptr<vertex<V, E> > st_ptr;
    st_ptr = add_vertex(vertex_start_name);
    std::weak_ptr<vertex<V, E> > f_ptr;
    f_ptr = add_vertex(vertex_finish_name);
    std::pair<std::weak_ptr<vertex<V, E> >, E> edg_1(f_ptr, weight);
    std::pair<std::weak_ptr<vertex<V, E> >, E> edg_2(st_ptr, weight);
    st_ptr.lock()->edges_from.insert(edg_1);
    f_ptr.lock()->edges_to.insert(edg_2);
    return;
}

template<typename V, typename E>
void graph<V, E>::remove_vertex(V name) throw (my::exception) {
    typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::iterator itr_main_map;
    itr_main_map = this->vertices.find(name);
    if (itr_main_map == this->vertices.end()) {
        throw(new my::exception("The vertex does not exist"));
    } else {
        typename std::map<std::weak_ptr <vertex<V, E> >, E >::iterator itr_adj;
        for (itr_adj = itr_main_map->second->edges_to.begin(); itr_adj != itr_main_map->second->edges_to.end(); ++itr_adj) {
                std::weak_ptr<vertex<V, E> > v_1 = itr_adj->first;
                v_1.lock()->edges_from.erase(itr_main_map->second);
        }
        for (itr_adj = itr_main_map->second->edges_from.begin(); itr_adj != itr_main_map->second->edges_from.end(); ++itr_adj) {
                std::weak_ptr<vertex<V, E> > v_1 = itr_adj->first;
                v_1.lock()->edges_to.erase(itr_main_map->second);
        }
        this->vertices.erase(name);
    }
}

template<typename V, typename E>
void graph<V, E>::remove_edge(V vertex_start_name, V vertex_finish_name) throw (my::exception) {
    typename std::unordered_map<V, std::shared_ptr<vertex<V, E>> >::iterator itr_main_map_start, itr_main_map_finish;
    itr_main_map_start = this->vertices.find(vertex_start_name);
    itr_main_map_finish = this->vertices.find(vertex_finish_name);
    if (itr_main_map_start == this->vertices.end()) {
        throw (new my::exception("The vertex does not exist: " + vertex_start_name));
    }
    if (itr_main_map_finish == this->vertices.end()) {
        throw (new my::exception("The vertex does not exist: " + vertex_finish_name));
    }
    typename std::map<std::weak_ptr<vertex<V, E> >, E>::iterator itr_adj;
    itr_adj = itr_main_map_start->second->edges_from.find(itr_main_map_finish->second);
    if (itr_adj == itr_main_map_start->second->edges_from.end()) {
        throw (new my::exception("The edge does not exist"));
    } else {
        itr_main_map_finish->second->edges_to.erase(itr_main_map_start->second);
        itr_main_map_start->second->edges_from.erase(itr_main_map_finish->second);
    }
}

template <typename V, typename E>
typename graph<V, E>::iteratorBFS graph<V, E>::BFSbegin() {
    return iteratorBFS(this, this->vertices.begin()->second);
}

template <typename V, typename E>
typename graph<V, E>::iteratorBFS graph<V, E>::BFSend() {
    return end_itr_BFS;
}

template <typename V, typename E>
void graph<V, E>::clear() {
        graph<char, int>::iteratorBFS itrBFS;
        for (itrBFS = this->DFSbegin(); itrBFS != this->BFSend(); ++itrBFS) {
            std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
            for (itr_adj = itrBFS->edges_from.cbegin(); itr_adj != itrBFS->edges_from.cend(); ++itr_adj) {
                this->remove_edge(itrBFS->name, itr_adj->first.lock()->name);
            }
        }
        for (itrBFS = this->BFSbegin(); itrBFS != this->BFSend(); ++itrBFS) {
            this->remove_vertex(itrBFS->name);
        }
}

template <typename V, typename E>
graph<V, E>& graph<V, E>::operator =(graph<V, E>& other) {
    graph<char, int>::iteratorBFS itrBFS;
    this->clear;
    for (itrBFS = other.BFSbegin(); itrBFS != other.BFSend(); ++itrBFS) {
        this->add_vertex(itrBFS->name);
        std::map<std::weak_ptr<vertex<char, int> >, int>::const_iterator itr_adj;
        for (itr_adj = itrBFS->edges_from.cbegin(); itr_adj != itrBFS->edges_from.cend(); ++itr_adj) {
            this->add_edge(itrBFS->name, itr_adj->first.lock()->name,  itr_adj->second);
        }
    }
    this->my_null = other.my_null;
    this->end_itr_BFS = other.end_itr_BFS;

}

#endif // IMPLEMENTATION_GRAPH_H
