#ifndef FIBHEAP_H
#define FIBHEAP_H
#include <set>
#include <vector>

template <typename K, typename V, typename Compare = std::less<K> >
class FibHeap {
    struct Node {
        std::weak_ptr<Node> parent = FibHeap::NIL;
        std::weak_ptr<Node> child = FibHeap::NIL;
        std::weak_ptr<Node> left;
        std::weak_ptr<Node> right;
        int degree = 0;
        bool mark = false;
        K key;
        V value;
        Node(K _key, V _value): key(_key), value(_value){;}
        friend std::ostream& operator << (std::ostream& ostr, std::shared_ptr<Node> const & node)  {
            ostr << node->key << " (" << node->value << ") ";
            return ostr;
        }
    };

    std::set<std::shared_ptr<Node> > nodes;
    std::weak_ptr<Node> min;
    int number_of_nodes = 0;
    static std::shared_ptr<Node> NIL;
    Compare comp;
public:
    FibHeap() {
        min = NIL;
    }
    ~FibHeap() {}

private:
    std::weak_ptr<Node> createNode(K key, V value) {
        typename std::set<std::shared_ptr<Node> >::iterator itr;
        itr = nodes.insert(std::shared_ptr<Node>(new Node(key, value))).first;
        (*itr)->left = (*itr);
        (*itr)->right = (*itr);
        return (*itr);
    }

    void insertToFibHeap(std::weak_ptr<Node> node) {
        if (min == NIL || comp(node.lock()->key, min.lock()->key)) {
            min = node;
        }
        ++number_of_nodes;
    }


    void unionFibHeapToThis(FibHeap && other_heap) {
        if (this->min != NIL && other_heap.min != NIL) {
            std::weak_ptr<Node> left_of_this_min = this->min.lock()->left;
            std::weak_ptr<Node> right_of_other_min = other_heap.min.lock()->right;
            this->min.lock()->left = other_heap.min;
            other_heap.min.lock()->right = this->min;
            left_of_this_min.lock()->right = right_of_other_min;
            right_of_other_min.lock()->left = left_of_this_min;
        }
        if (this->min == NIL || (other_heap.min !=NIL && comp(other_heap.min.lock()->key,this->min.lock()->key))) {
            this->min = other_heap.min;
        }
        this->nodes.insert(other_heap.nodes.cbegin(), other_heap.nodes.cend());
        this->number_of_nodes += other_heap.number_of_nodes;
    }

    void consolidate() {
        std::vector<std::weak_ptr<Node> > vector_of_roots(number_of_nodes);
        for (int i = 0; i != this->number_of_nodes; ++ i) {
            vector_of_roots.push_back(NIL);
        }
        std::weak_ptr<Node> one_of_root = this->min;
        do {
            std::weak_ptr<Node> x = one_of_root;
            int d = x.lock()->degree;
            while (vector_of_roots[d] != NIL) {
                std::weak_ptr<Node> y = vector_of_roots[d];
                if (comp(x.lock()->key, y.lock()->key)) {
                    std::weak_ptr<Node> buf = x;
                    x = y;
                    y = buf;
                }
                link(y, x);
                vector_of_roots[d] = NIL;
                ++d;
            }
            vector_of_roots[d] = x;
            one_of_root = one_of_root.lock()->right;
        } while (one_of_root != this->min); // нет ли здесь проблемы с тем, чьл минимум, или ссылка левого соседа на мин поменялись?
                                                //нет, минимум как был корнем, так и остался им
        this->min = NIL;
        for (int i = 0; i < this->number_of_nodes; ++i) {
            if (vector_of_roots[i] != NIL) {
                vector_of_roots[i].lock()->parent = NIL;
                this->min.lock()->left.lock()->right = vector_of_roots[i];
                vector_of_roots[i].lock()->left = this->min.lock()->left;
                this->min.lock()->left = vector_of_roots[i];
                vector_of_roots[i].lock()->right = this->min;
                if (this->min == NIL || comp(vector_of_roots[i].lock()->key, this->min.lock()->key)) {
                    this->min = vector_of_roots[i];
                }
            }
        }
    }


    void link(std::weak_ptr<Node> y, std::weak_ptr<Node> x) {
        y.lock()->left.lock()->right = y.lock()->right.lock();
        y.lock()->right.lock()->left = y.lock()->left;
        y.lock()->right = x.lock()->child;
        y.lock()->left = x.lock()->child.lock()->left;
        x.lock()->child.lock()->left.lock()->right = y;
        x.lock()->child.lock()->left = y;
        ++x.lock()->degree;
        y.lock()->parent = x;
        y.lock()->mark = false;
    }

public:
    std::weak_ptr<Node> insert(K key, V value) {
        std::weak_ptr<Node> node = this->createNode(key, value);
        this->insertToFibHeap(node);
        return node;
    }

    std::weak_ptr<Node> extractMin() {
        std::weak_ptr<Node> z = this->min;
        if (z != NIL) {
            std::weak_ptr<Node> child = z.lock()->child;
            if (child != NIL) {
                std::weak_ptr<Node> next = child.lock()->right;
                do {
                    std::weak_ptr<Node> min_left = this->min.lock()->left;
                    next.lock()->right.lock()->left = next.lock()->left;
                    next.lock()->left.lock()->right = next.lock()->right;
                    next.lock()->parent = NIL;
                    this->min.lock()->left = next;
                    next.lock()->right = this->min;
                    min_left.lock()->right = next;
                    next.lock()->left = min_left;
                } while (next != child);
            }
            z.lock()->left.lock()->right = z.lock()->right;
            z.lock()->right.lock()->left = z.lock()->left;
            if (z == z.lock()->right) {
                this->min = NIL;
            } else {
                this->min = z.lock()->right;
                consolidate();
            }
            --number_of_nodes;
        }
        return z;
    }


};

template <typename K, typename V, typename Compare>
std::shared_ptr<typename FibHeap<K, V, Compare>::Node> FibHeap<K, V, Compare>::NIL = nullptr;


#endif // FIBHEAP_H
