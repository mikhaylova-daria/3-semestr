#ifndef ITERATORS_H
#define ITERATORS_H
template <typename V, typename E>
class graph<V, E>::iteratorBFS {

    struct BFS_vertex_characterization {
        std::weak_ptr<vertex<V, E> > parent;
        char color;
    };

    std::unordered_map<V, BFS_vertex_characterization> status;
    std::queue<std::weak_ptr<vertex<V, E> > > gray;
    std::weak_ptr<vertex<V, E> > current;
    const graph<V, E>* g;
    int number_of_black = 0;

public:
    friend class graph<V, E>;
    iteratorBFS() {;}

private:
    iteratorBFS(const graph<V, E> *G, V start_name) {
        g = G;
        std::weak_ptr <vertex<V, E> > start = G->vertices.find(start_name)->second;
        BFS_vertex_characterization description;
        description.color = 0;
        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
        for (itr = G->vertices.cbegin(); itr != G->vertices.cend(); ++itr) {
            status.insert(std::pair<V, BFS_vertex_characterization>(itr->first, description));
        }
        typename std::unordered_map<V, BFS_vertex_characterization>::iterator itr_status;
        itr_status = status.find(start.lock()->name);
        itr_status->second.color = 1;
        gray.push(start);
        this->operator++();
    }

public:
    iteratorBFS& operator++() {
        if (!gray.empty()) {
            current = gray.front();
            gray.pop();
            typename std::list<std::pair<std::weak_ptr <vertex<V, E> >, E> >::const_iterator itr_adj;
            for (itr_adj = current.lock()->edges_from.cbegin(); itr_adj != current.lock()->edges_from.cend(); ++itr_adj) {
                BFS_vertex_characterization status_of_current;
                status_of_current = status.find((*itr_adj).first.lock()->name)->second;
                if (status_of_current.color == 0) {
                    status_of_current.color = 1;
                    status_of_current.parent = current;
                    gray.push(itr_adj->first);
                }
            }
            status.find(current.lock()->name)->second.color = 2;
            ++number_of_black;
        } else {
            if (number_of_black != g->vertices.size()) {
                typename std::unordered_map<V, BFS_vertex_characterization>::iterator itr_st = status.begin();
                while (itr_st->second.color != 0) {
                    ++itr_st;
                }
                itr_st->second.color = 1;
                std::weak_ptr<vertex<V, E> >new_working_vertex = g->vertices.find(itr_st->first)->second;
                gray.push(new_working_vertex);
                this->operator++();
            } else {
                status.clear();
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
        g = oth.g;
        status.insert(oth.status.begin(), oth.status.end());
        gray = gray;
        current = oth.current;
        return (*this);
    }

    bool operator==(const iteratorBFS& oth) {
        if (status.size() != 0 && oth.status.size() != 0) { //для сравнения с end(), в остальных случаях проверяет равенство вершин
            return (current.lock().get() == oth.current.lock().get());
        } else {
            return (status.size() == 0 && oth.status.size() == 0);
        }
    }

    bool operator!=(const iteratorBFS& oth) {
        return !(*this == oth);
    }

};
#endif // ITERATORS_H
