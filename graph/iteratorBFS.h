#ifndef ITERATORBFS_H
#define ITERATORBFS_H
template <typename V, typename E>
class graph<V, E>::iteratorBFS {

    struct BFS_vertex_characterization {
        std::weak_ptr<vertex<V, E> > parent;
        char color;
    };

    std::map<std::weak_ptr<vertex<V, E>>, BFS_vertex_characterization> status;
    std::queue<std::weak_ptr<vertex<V, E> > > gray;
    std::weak_ptr<vertex<V, E> > current;
    graph<V, E>* g;
    int number_of_black = 0;

public:
    friend class graph<V, E>;
    iteratorBFS() {
    }
    ~iteratorBFS() {
    }

private:
    iteratorBFS(graph<V, E> *G, std::weak_ptr<vertex<V, E> > start) {
        g = G;
        BFS_vertex_characterization description;
        description.color = 0;
        description.parent = g->my_null;
        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
        for (itr = G->vertices.cbegin(); itr != G->vertices.cend(); ++itr) {
            status.insert(std::pair<std::weak_ptr<vertex<V, E> >, BFS_vertex_characterization>(itr->second, description));
        }
        typename std::map<std::weak_ptr<vertex<V, E> >, BFS_vertex_characterization>::iterator itr_status;
        itr_status = status.find(start);
        itr_status->second.color = 1;
        gray.push(start);
        this->operator++();
    }

public:
    iteratorBFS& operator++() {
        if (!gray.empty()) {
            current = gray.front();
            gray.pop();
            typename std::map<std::weak_ptr <vertex<V, E> >, E>::const_iterator itr_adj;
            for (itr_adj = current.lock()->edges_from.cbegin(); itr_adj != current.lock()->edges_from.cend(); ++itr_adj) {
                typename std::map<std::weak_ptr<vertex<V, E> >,  BFS_vertex_characterization>::iterator itr_st;
                itr_st = status.find(itr_adj->first);
                if (itr_st != status.end()) {
                    if (itr_st->second.color == 0) {
                        itr_st->second.color = 1;
                        itr_st->second.parent = current;
                        gray.push(itr_adj->first);
                    }
                }
            }
            status.erase(current);
            ++number_of_black;
        } else {
            if (number_of_black < g->vertices.size()) {
                std::weak_ptr<vertex<V, E> > new_working_vertex = status.begin()->first;
                status.begin()->second.color = 1;
                gray.push(new_working_vertex);
                this->operator++();
            } else {
                this->current = g->my_null;
            }
        }
        return *this;
    }

    vertex<V, E>& operator*() const {
        return (*current.lock().get());
    }

    vertex<V, E>* operator->() const {
        return current.lock().get();
    }

    iteratorBFS& operator=(const iteratorBFS& oth) {
        if (this != &oth) {
            g = oth.g;
            number_of_black = oth.number_of_black;
            status.clear();
            status.insert(oth.status.begin(), oth.status.end());
            gray = oth.gray;
            current = oth.current;
        }
        return (*this);
    }

    bool operator==(const iteratorBFS& oth) const {
        return current.lock().get() == oth.current.lock().get();
    }

    bool operator!=(const iteratorBFS& oth) const {
        return this->current.lock().get() != oth.current.lock().get();
    }

};
#endif // ITERATORBFS_H


