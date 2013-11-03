#ifndef ITERATORBFS_H
#define ITERATORBFS_H
//template <typename V, typename E>
//class graph<V, E>::iteratorBFS {

//    struct BFS_vertex_characterization {
//        std::weak_ptr<vertex<V, E> > parent;
//        char color;
//    };

//    std::unordered_map<V, BFS_vertex_characterization> status;
//    std::queue<std::weak_ptr<vertex<V, E> > > gray;
//    std::weak_ptr<vertex<V, E> > current;
//    const graph<V, E>* g;
//    int number_of_black = 0;
//    std::shared_ptr<vertex<V, E> > my_null;

//public:
//    friend class graph<V, E>;
//    iteratorBFS() {
//    }
//    ~iteratorBFS() {
//    }

//private:
//    iteratorBFS(const graph<V, E> *G, V start_name) {
//        g = G;
//        my_null = std::shared_ptr<vertex<V, E> >(new vertex<V, E>());
//        std::weak_ptr <vertex<V, E> > start = G->vertices.find(start_name)->second;
//        BFS_vertex_characterization description;
//        description.color = 0;
//        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
//        for (itr = G->vertices.cbegin(); itr != G->vertices.cend(); ++itr) {
//            status.insert(std::pair<V, BFS_vertex_characterization>(itr->first, description));
//        }
//        typename std::unordered_map<V, BFS_vertex_characterization>::iterator itr_status;
//        itr_status = status.find(start.lock()->name);
//        itr_status->second.color = 1;
//        gray.push(start);
//        this->operator++();
//    }

//public:
//    iteratorBFS& operator++() {
//        if (!gray.empty()) {
//            if (number_of_black > 0) {
//                status.erase(current.lock()->name);
//            }
//            current = gray.front();
//            gray.pop();
//            typename std::list<std::pair<std::weak_ptr <vertex<V, E> >, E> >::const_iterator itr_adj;
//            for (itr_adj = current.lock()->edges_from.cbegin(); itr_adj != current.lock()->edges_from.cend(); ++itr_adj) {
//                typename std::unordered_map<V,  BFS_vertex_characterization>::iterator itr_st = status.find((*itr_adj).first.lock()->name);
//                if (itr_st != status.end()) {
//                    BFS_vertex_characterization status_of_current;
//                    status_of_current = itr_st->second;
//                    if (status_of_current.color == 0) {
//                        status_of_current.color = 1;
//                        status_of_current.parent = current;
//                        gray.push(itr_adj->first);
//                    }
//                }
//            }
//            ++number_of_black;
//        } else {
//            if (!status.empty()) {
//                std::weak_ptr<vertex<V, E> >new_working_vertex = g->vertices.find(status.begin()->first)->second;
//                status.begin()->second.color = 1;
//                gray.push(new_working_vertex);
//                this->operator++();
//            }
//        }
//        return *this;
//    }

//    vertex<V, E>& operator*() const {
//        return (*current.lock().get());
//    }

//    vertex<V, E>* operator->() const {
//        return current.lock().get();
//    }

//    iteratorBFS& operator=(const iteratorBFS& oth) {
//        g = oth.g;
//        status.insert(oth.status.begin(), oth.status.end());
//        gray = gray;
//        current = oth.current;
//        return (*this);
//    }

//    bool operator==(const iteratorBFS& oth) {
//        if (status.size() != 0 && oth.status.size() != 0) { //для сравнения с end(), в остальных случаях проверяет равенство вершин
//            return (current.lock().get() == oth.current.lock().get());
//        } else {
//            return (status.size() == 0 && oth.status.size() == 0);
//        }
//    }

//    bool operator!=(const iteratorBFS& oth) {
//        return !(*this == oth);
//    }

//};
#endif // ITERATORBFS_H
