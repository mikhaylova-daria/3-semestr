#ifndef BINHEAP_H
#define BINHEAP_H
#include <memory>
#include <list>
#include "libr.h"


template <typename K, typename V = int, typename Compare = std::less<K> >
class BinomialHeap {
public:
    class Node {
        K key;
        int degree;
        Node(){}
        Node (const K & _key): key(_key){}
        Node(const K & _key, const V & _value): key(_key), value(_value){}
    public:
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> sibling;
        std::shared_ptr<Node> child;
        V value;
        ~Node(){}

        static std::shared_ptr<Node> createNode(K _key, V _value) {
            std::shared_ptr<Node> newNode(new Node(_key, _value));
            return newNode;
        }

        static std::shared_ptr<Node> createNode(K _key) {
            std::shared_ptr<Node> newNode(new Node(_key));
            return newNode;
        }

        K getKey() {
            return key;
        }

        friend std::ostream& operator << (std::ostream& ostr, std::shared_ptr<Node> const & node)  {
            ostr << node->key << " (" << node->value << ") ";
            return ostr;
        }

        friend class BinomialHeap;
    };

private:
    std::shared_ptr<Node> head;
    static std::shared_ptr<Node> NIL;
    K absMin;
    K absMax;
    Compare comp;
    static int numberOfHeap;

public:

    BinomialHeap(K infinity, K _absMin) {
        if (NIL.get() == nullptr) {
            NIL = std::make_shared<Node>(*(new Node()));
            NIL -> parent = NIL;
            NIL -> child = NIL;
            NIL ->sibling = NIL;
        }
        head = NIL;
        absMax = infinity;
        absMin = _absMin;
    }

    ~BinomialHeap(){
        --numberOfHeap;
    }

    std::shared_ptr<Node> binomialHeapMinimum() {//!
        std::shared_ptr<Node> y = NIL;
        std::shared_ptr<Node> x = head;
        K min = absMax;
        while (x != NIL) {
            if (comp(x->key, min)) {
                min = x->key;
                y = x;
            }
            x = x->sibling;
        }
        return y;
    }

    bool isEmpty() {
        if (head != NIL) {
            return false;
        } else {
            return true;
        }
    }

    void binomialLinkTreeSecondWillBeRoot(std::shared_ptr<Node> rootOfFirst, std::shared_ptr<Node> rootOfSecond) {
        rootOfFirst->parent = rootOfSecond;
        rootOfFirst->sibling = rootOfSecond->child;
        rootOfSecond->child = rootOfFirst;
        rootOfSecond->degree += 1;
        return;
    }

    std::shared_ptr<Node> binomialHeapMerge(std::shared_ptr<Node> first, std::shared_ptr<Node> second){
        std::shared_ptr<Node> resultListHead;
        std::shared_ptr<Node> currentRoot;
        if (first->degree < second->degree) {
            resultListHead = first;
            first = first->sibling;
        } else {
            resultListHead = second;
            second = second->sibling;
        }
        currentRoot = resultListHead;
        while (first != NIL && second != NIL) {
            if (first->degree < second->degree) {
                currentRoot->sibling = first;
                first = first->sibling;
            } else {
                currentRoot->sibling = second;
                second = second->sibling;
            }
            currentRoot = currentRoot->sibling;
        }
        if (first != NIL) {
            currentRoot->sibling = first;
        }
        if (second != NIL) {
            currentRoot->sibling = second;
        }
        return resultListHead;
    }

    void unionWith(BinomialHeap& otherHeap) {
        this->head = binomialHeapMerge(this->head, otherHeap.head);
        if (head != NIL) {
            std::shared_ptr<Node> prev_x = NIL;
            std::shared_ptr<Node> x = head;
            std::shared_ptr<Node> next_x = x->sibling;
            while (next_x != NIL) {
                if ((x->degree != next_x->degree)
                        || (next_x->sibling != NIL && next_x->sibling->degree == x->degree)) {
                    prev_x = x;
                    x = next_x;
                } else {
                    if (comp(x->key, next_x->key)) {
                        x->sibling = next_x->sibling;
                        binomialLinkTreeSecondWillBeRoot(next_x, x);
                    } else {
                        if (prev_x == NIL) {
                            head = next_x;
                        } else {
                            prev_x->sibling = next_x;
                        }
                        binomialLinkTreeSecondWillBeRoot(x, next_x);
                        x = next_x;
                    }
                }
                next_x = x->sibling;
            }
        }
    }


    std::shared_ptr<Node> binomialHeapExtractMin() {
        std::shared_ptr<Node> min = binomialHeapMinimum();
        std::shared_ptr<Node> headOfListOfChildren = min->child;
        std::shared_ptr<Node> buf;
        std::shared_ptr<Node> next = headOfListOfChildren->sibling;
        if (min == head) {
            head = min->sibling;
        } else {
            std::shared_ptr<Node> buf_node = head;
            std::shared_ptr<Node> prev_min;
            while (buf_node != min) {
                prev_min = buf_node;
                buf_node = buf_node->sibling;
            }
            prev_min->sibling = min->sibling;
        }
        if (min->child == NIL) {
            return min;
        }
        while (next != NIL) {
            headOfListOfChildren->parent = NIL;
            buf = headOfListOfChildren;
            headOfListOfChildren = next;
            next = headOfListOfChildren->sibling;
            headOfListOfChildren->sibling = buf;
        }
        min->child->sibling = NIL;
        BinomialHeap helper(absMax, absMin);
        helper.head = headOfListOfChildren;
        this->unionWith(helper);
        return min;
    }

    void binomialHeapInsert(std::shared_ptr<Node> x) {
        x->parent = NIL;
        x->child = NIL;
        x->sibling = NIL;
        x->degree = 0;
        BinomialHeap helpHeap(absMax, absMin);
        helpHeap.head = x;
        this->unionWith(helpHeap);
    }

    K binomialHeapDecreaseKey(std::shared_ptr<Node> node, K newKey) {
        if (comp(node->key, newKey)) {
            throw (my::exception("New key is bigger then current"));
        }
        K oldKey = node->key;
        node->key = newKey;
        std::shared_ptr<Node> y = node;
        std::shared_ptr<Node> z = y->parent.lock();
        while (z != NIL && comp(y->key, z->key)) {
            std::shared_ptr<Node> buf_parent_y = y->parent.lock();
            std::shared_ptr<Node> buf_parent_z = z->parent.lock();
            std::shared_ptr<Node> buf_child =  y->child;
            std::shared_ptr<Node> buf_sibling =  y->sibling;
            y->parent = z->parent;
            y->child = z->child;
            y->sibling = z->sibling;
            z->parent = buf_parent_y;
            z->child = buf_child;
            z->sibling = buf_sibling;
            std::shared_ptr<Node> buf_node = buf_parent_y->child;
            if (buf_node != y) {
                while (buf_node->sibling != y) {
                    buf_node = buf_node->sibling;
                }
                buf_node->sibling = z;
            }
            buf_node = buf_parent_z->child;
            if (buf_node != z) {
                while (buf_node->sibling != z) {
                    buf_node = buf_node->sibling;
                }
                buf_node->sibling = y;
            }
            y = z;
            z = y->parent.lock();
        }
        return oldKey;
    }

    std::shared_ptr<Node>binomialHeapDelete(std::shared_ptr<Node> node) {
        K key = binomialHeapDecreaseKey(node, absMin);
        std::shared_ptr<Node> result = binomialHeapExtractMin();
        result->key = key;
        return result;
    }

    std::shared_ptr<Node> put(K key) {
        if (comp(absMax, key)) {
            throw(my::exception("This key is more then plus infinity"));
        }
        if (comp(key, absMin)) {
            throw(my::exception("This key is less then minus infinity"));
        }
        std::shared_ptr<Node> newNode = Node::createNode(key);
        this->binomialHeapInsert(newNode);
        return newNode;
    }

    std::shared_ptr<Node> put(K key, V value) {
        if (comp(absMax, key)) {
            throw(my::exception("This key is more then plus infinity"));
        }
        if (comp(key, absMin)) {
            throw(my::exception("This key is less then minus infinity"));
        }
        std::shared_ptr<Node> newNode = Node::createNode(key, value);
        this->binomialHeapInsert(newNode);
        return newNode;
    }

    bool increasePlusInfinity(K infinity) {
        if (comp(infinity, absMax)) {
            return false;
        } else {
            absMax = infinity;
            return true;
        }
    }

    bool decreaseMinusInfinity(K infinity) {
        if (comp(absMin, infinity)) {
            return false;
        } else {
            absMin = infinity;
            return true;
        }

    }

    std::list<std::shared_ptr<Node> > getNodesList() {
        std::list<std::shared_ptr<Node> > answer;
        std::shared_ptr<Node> node = this->head;
        answer.push_back(node);
        while (node != NIL) {
            this->get_children(answer, node);
            node = node ->sibling;
        }
        return answer;
    }

    friend std::istream& operator >>  (std::istream& istr, BinomialHeap<K, V, Compare> & heap){
        K key;
        V value;
        std::shared_ptr<Node> last;
        istr >> key >> value;
        while (!istr.eof()) {
            last = heap.put(key, value);
            istr >> key >> value;
        }
        return istr;
    }

    friend std::ostream& operator << (std::ostream& ostr, BinomialHeap<K, V, Compare> & heap)  {
        std::shared_ptr<Node> node = heap.head;
        int count_tab = 0;
        while (node != NIL) {
            ostr << node << "\n";
            ++count_tab;
            heap.print_children(ostr, node, count_tab);
            --count_tab;
            node = node ->sibling;
            ostr << "\n\n";
        }
        return ostr;
    }

private:
    void print_children(std::ostream& ostr, std::shared_ptr<Node> node, int count_tab) {
        node = node->child;
        while (node != this->NIL) {
            for (int i = 0; i < count_tab; ++i) {
                ostr << "\t";
            }
            ostr << node << "\n";
            ++count_tab;
            print_children(ostr, node, count_tab);
            --count_tab;
            node = node->sibling;
        }
        return;
    }

    void get_children(std::list<std::shared_ptr<Node> >& answer, std::shared_ptr<Node> node) {
        node = node->child;
        while (node != this->NIL) {
            answer.push_back(node);
            get_children(answer, node);
            node = node->sibling;
        }
        return;
    }
};


template <typename K, typename V, typename Compare>
int BinomialHeap<K, V, Compare>::numberOfHeap = 0;

template <typename K, typename V, typename Compare>
std::shared_ptr<typename BinomialHeap<K, V, Compare>::Node> BinomialHeap<K, V, Compare>::NIL = nullptr;

#endif // BINHEAP_H
