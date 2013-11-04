#ifndef ITERATORDFS_H
#define ITERATORDFS_H
#include <stack>
#include <unordered_map>
#include <unordered_set>
template <typename V, typename E>
class graph<V, E>::iteratorDFS {

    struct DFS_vertex_characterization {
        std::weak_ptr<vertex<V, E> > parent;
        std::weak_ptr<vertex<V, E> > ptr;
        typename std::map<std::weak_ptr<vertex<V, E> >, E>::const_iterator next_child;
        char color = 0;
        int discover = 0;
        int finish = 0;
    };

    std::unordered_map<V, DFS_vertex_characterization> status;
    std::stack<std::weak_ptr<vertex<V, E> > > discovered;
    std::weak_ptr<vertex<V, E> > current;
    const graph<V, E>* g;
    int number_of_visit = 0;
    std::unordered_set<V> unfinished;

public:
    friend class graph<V, E>;
    iteratorDFS() {
    }
    ~iteratorDFS() {
    }

private:
    iteratorDFS(const graph<V, E> *G, std::weak_ptr<vertex<V, E> > start) {
        g = G;
        DFS_vertex_characterization description;
        description.parent = g->my_null;
        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
        for (itr = G->vertices.cbegin(); itr != G->vertices.cend(); ++itr) {
            description.ptr = itr->second;
            description.next_child = itr->second->edges_from.cbegin();
            status.insert(std::pair<V, DFS_vertex_characterization>(itr->first, description));
            unfinished.insert(itr->first);
        }
        typename std::unordered_map<V, DFS_vertex_characterization>::iterator itr_status;
        itr_status = status.find(start.lock()->name);
        itr_status->second.color = 1;
        itr_status->second.discover = number_of_visit;
        ++number_of_visit;
        discovered.push(itr_status->second.ptr);
        current = start;
    }

public:
    iteratorDFS& inc() {
        if (!discovered.empty()) {
            std::weak_ptr<vertex<V, E> > current_front = discovered.top();
            typename std::unordered_map<V, DFS_vertex_characterization>::iterator itr_st;
            itr_st = status.find(current_front.lock()->name);
            if (itr_st != status.end()) {
                if (itr_st->second.next_child != itr_st->second.ptr.lock()->edges_from.cend()) {
                    typename std::unordered_map<V, DFS_vertex_characterization>::iterator itr_st_next;
                    itr_st_next = status.find(itr_st->second.next_child->first.lock()->name);
                    while (itr_st_next->second.color != 0) {
                        ++itr_st->second.next_child;
                        if (itr_st->second.next_child == itr_st->second.ptr.lock()->edges_from.cend()) {
                            break;
                        }
                        itr_st_next = status.find(itr_st->second.next_child->first.lock()->name);
                    }
                    if (itr_st->second.next_child != itr_st->second.ptr.lock()->edges_from.cend()) {
                        discovered.push(itr_st->second.next_child->first);
                        itr_st_next->second.color = 1;
                        itr_st_next->second.parent = itr_st->second.ptr;
                        itr_st_next->second.discover = number_of_visit;
                        ++number_of_visit;
                        current = itr_st_next->second.ptr;
                        ++(itr_st->second.next_child);
                    } else {
                        itr_st->second.color = 2;
                        itr_st->second.finish = number_of_visit;
                        ++number_of_visit;
                        discovered.pop();
                        unfinished.erase(itr_st->first);
                        current = itr_st->second.ptr;
                    }
                } else {
                    if (!unfinished.empty()) {
                        itr_st->second.color = 2;
                        itr_st->second.finish = number_of_visit;
                        ++number_of_visit;
                        discovered.pop();
                        unfinished.erase(itr_st->first);
                        current = itr_st->second.ptr;
                    } else {
                        current = g->my_null;
                    }
                }
            }
        } else {
            if (!unfinished.empty()) {
                typename std::unordered_map<V, DFS_vertex_characterization>::iterator itr_status;
                itr_status = status.find(*unfinished.begin());
                itr_status->second.color = 1;
                itr_status->second.discover = number_of_visit;
                itr_status->second.parent = current;
                ++number_of_visit;
                discovered.push(itr_status->second.ptr);
                current = itr_status->second.ptr;
            } else {
                current =g->my_null;
            }
        }
        return *this;
    }

    iteratorDFS& begin() {
        while(this->get_color_DFS() != 2) {
            inc();
        }
        return *this;
    }

    iteratorDFS& operator++() {
        inc();
        while(this->get_color_DFS() != 2) {
            inc();
        }
        return *this;
    }

    vertex<V, E>& operator*() const {
        return (*current.lock().get());
    }

    vertex<V, E>* operator->() const {
        return current.lock().get();
    }

    int get_color_DFS() {
        if (current.lock().get() == g->my_null.get()) {
            return 2;
        }
        typename std::unordered_map<V, DFS_vertex_characterization>::const_iterator itr_st;
        itr_st = status.find(current.lock()->name);
        return itr_st->second.color;
    }

    iteratorDFS& operator=(iteratorDFS oth) {
        if (this != &oth) {
            g = oth.g;
            status.clear();
            status.insert(oth.status.begin(), oth.status.end());
            status.insert(oth.status.cbegin(), oth.status.cend());
            std::stack<std::weak_ptr<vertex<V, E> > > st;

            while (!oth.discovered.empty()) {
                st.push(oth.discovered.top());
                oth.discovered.pop();
            }
            while (!st.empty()) {
                oth.discovered.push(st.top());
                discovered.push(st.top());
                st.pop();
            }
            number_of_visit = oth.number_of_visit;
            unfinished.clear();
            unfinished.insert(oth.unfinished.cbegin(), oth.unfinished.cend());
            current = oth.current;
        }
        return (*this);
    }

    bool operator==(const iteratorDFS& oth) const {
        return current.lock().get() == oth.current.lock().get();
    }

    bool operator!=(const iteratorDFS& oth) const {
        return this->current.lock().get() != oth.current.lock().get();
    }

};
#endif // ITERATORDFS_H
