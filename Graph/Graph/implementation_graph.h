#ifndef IMPLEMENTATION_GRAPH_H
#define IMPLEMENTATION_GRAPH_H

#include <queue>

template <typename V, typename E>
bool operator < (std::weak_ptr<vertex<V, E> > ptr, std::weak_ptr<vertex<V, E> > other_ptr){
    return (ptr.lock())->name < (other_ptr.lock())->name;
}

template <typename V, typename E>
bool operator == (std::weak_ptr<vertex<V, E> > ptr, std::weak_ptr<vertex<E, V> > other_ptr){
    return (ptr.lock())->name == (other_ptr.lock())->name;
}

template <typename V, typename E>
graph<V, E>::graph() {
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
    st_ptr.lock()->edges_from.push_back(edg_1);
    f_ptr.lock()->edges_to.push_back(edg_2);
    return;
}

template <typename V, typename E>
typename graph<V, E>::iteratorBFS graph<V, E>::begin() {
    return iteratorBFS(this, (*(this->vertices.begin())).first);
}

template <typename V, typename E>
typename graph<V, E>::iteratorBFS graph<V, E>::end() {
    iteratorBFS itr;
    return itr;
}



#endif // IMPLEMENTATION_GRAPH_H
