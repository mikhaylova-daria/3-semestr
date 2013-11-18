#ifndef ITERATORDFS_H
#define ITERATORDFS_H
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
template <typename V, typename E>
class graph<V, E>::iteratorDFS {

    struct DFS_vertex_characterization {
        std::weak_ptr<vertex<V, E> > parent;
        std::weak_ptr<vertex<V, E> > ptr;
        typename std::map<std::weak_ptr<vertex<V, E> >, E>::const_iterator next_child;
        char color = 0;       
        int discover = 2147483647;
        int finish = 2147483647;
    };

    std::unordered_map<V, DFS_vertex_characterization> status;
    std::stack<std::weak_ptr<vertex<V, E> > > discovered;
    std::stack<std::shared_ptr<vertex<V, E> > > stackDFS;
    std::shared_ptr<vertex<V, E> > current;
    const graph<V, E>* g;
    int number_of_visit = 0;
    std::unordered_set<V> undiscovered;
    bool last_was_finished = false;
    int time = 1;

public:
    int get_discovery_time() {
        return status.find(current->name)->second().discover;
    }
    int get_finish_time() {
        return status.find(current->name)->second().finish;
    }
    friend class graph<V, E>;
    iteratorDFS() {
    }
    ~iteratorDFS() {
    }

private:

    iteratorDFS(const graph<V, E> *G, std::shared_ptr<vertex<V, E> > start) {
        g = G;
        DFS_vertex_characterization description;
        description.parent = g->my_null;
        typename std::unordered_map<V, std::shared_ptr<vertex<V, E> > >::const_iterator itr;
        for (itr = G->vertices.cbegin(); itr != G->vertices.cend(); ++itr) {
            description.ptr = itr->second;
            description.next_child = itr->second->edges_from.cbegin();
            status.insert(std::pair<V, DFS_vertex_characterization>(itr->first, description));
            undiscovered.insert(itr->first);
        }
        status.find(start->name)->second.color = 1;
        status.find(start->name)->second.discover = time;
        ++time;
        stackDFS.push(start);
        typename std::map<std::weak_ptr<vertex<V, E> >, E>::iterator itr_adj;
        for (itr_adj = start->edges_from.begin(); itr_adj != start->edges_from.end(); ++ itr_adj){
            stackDFS.push(itr_adj->first.lock());
            status.find(itr_adj->first.lock()->name)->second.parent = start;
        }
        undiscovered.erase(start->name);
        current = start;
    }


public:


    iteratorDFS& begin() {
        return *this;
    }

    iteratorDFS& inc() {
        std::shared_ptr<vertex<V, E> > x;
        if (!stackDFS.empty()) {
            x = stackDFS.top();
            stackDFS.pop();
            if (status.find(x->name)->second.color == 0) {
                status.find(x->name)->second.color = 1;
                undiscovered.erase(x->name);
                status.find(x->name)->second.discover = time;
                ++time;
                stackDFS.push(x);
                typename std::map<std::weak_ptr<vertex<V, E> >, E>::iterator itr_adj;
                for (itr_adj = x->edges_from.begin(); itr_adj != x->edges_from.end(); ++ itr_adj){
                    if (status.find(itr_adj->first.lock()->name)->second.color == 0) {
                        stackDFS.push(itr_adj->first.lock());
                        status.find(itr_adj->first.lock()->name)->second.parent = x;
                    }
                }
            } else {
                 status.find(x->name)->second.finish = time;
                 ++time;
                 status.find(x->name)->second.color = 2;
            }
        } else {
            if (undiscovered.begin() == undiscovered.end()) {
                current = g->my_null;
                return *this;
            }
            x = g->vertices.find(*undiscovered.begin())->second;
            undiscovered.erase(x->name);
            status.find(x->name)->second.color = 1;
            status.find(x->name)->second.discover = time;
            ++time;
            stackDFS.push(x);
            typename std::map<std::weak_ptr<vertex<V, E> >, E>::iterator itr_adj;
            for (itr_adj = x->edges_from.begin(); itr_adj != x->edges_from.end(); ++ itr_adj){
                stackDFS.push(itr_adj->first.lock());
                status.find(itr_adj->first.lock()->name)->second.parent = x;
            }
        }
        current = x;
        return *this;
    }

    iteratorDFS& operator++() {
        while (true) {
            if (current == g->my_null) {
                break;
            }
            if (status.find(current->name)->second.color == 1) {
                this->inc();
                break;
            }
            this->inc();
        }
        return *this;
    }

    vertex<V, E>& operator*() const {
        return (*current.get());
    }

    vertex<V, E>* operator->() const {
        return current.get();
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
            time = oth.time;
            undiscovered.clear();
            undiscovered.insert(oth.undiscovered.begin(), oth.undiscovered.end());
            current = oth.current;
        }
        return (*this);
    }

    bool operator==(const iteratorDFS& oth) const {
        return current.get() == oth.current.get();
    }

    bool operator!=(const iteratorDFS& oth) const {
        return this->current.get() != oth.current.get();
    }

};
#endif // ITERATORDFS_H
