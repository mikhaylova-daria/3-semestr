#ifndef BINHEAP_H
#define BINHEAP_H
#include <memory>
#include "libr.h"


template <typename K, typename V = int, typename Compare = std::less<K> >
class BinomialHeap {
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

        friend class BinomialHeap;
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> NIL;
    K absMin;

public:
    Compare comp;
    BinomialHeap(K infinity, K _absMin) {
        std::shared_ptr<Node> buf(new Node());
        NIL = buf;
        head = NIL;
        NIL->key = infinity;
        absMin = _absMin;
    }

    ~BinomialHeap(){}

    std::shared_ptr<Node> binomialHeapMinimum() {
        std::shared_ptr<Node> y = NIL;
        std::shared_ptr<Node> x = head;
        K min = NIL->key;
        while (x != NIL) {
            if (comp(x->key, min)) {
                min = x->key;
                y = x;
            }
            x = x->sibling;
        }
        return y;
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
        if (first == NIL) {
            resultListHead = second;
            if (second == NIL) {
                return NIL;
            } else {
                second = second->sibling;
            }
        } else {
            if (second == NIL) {
                resultListHead = first;
                first = first->sibling;
            } else {
                if (first->degree < second->degree) {
                    resultListHead = first;
                    first = first->sibling;
                } else {
                    resultListHead = second;
                    second = second->sibling;
                }
            }
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
        } else {
            currentRoot->sibling = second;
        }
        return resultListHead;
    }

    std::shared_ptr<BinomialHeap> unionWith(BinomialHeap& otherHeap) {
        std::shared_ptr<BinomialHeap> heapResalt(new BinomialHeap(NIL->key, absMin));
        heapResalt->head = binomialHeapMerge(this->head, otherHeap.head);
        if (head != NIL) {
            std::shared_ptr<Node> prev_x = NIL;
            std::shared_ptr<Node> x = heapResalt->head;
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
                            heapResalt->head = next_x;
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
        return heapResalt;
    }
    struct ExtractResult {
        K key;  //ключ удалённого
        V value; // значение удалённого
        std::shared_ptr<Node> newPointerOnSibling;  //новый указатель сестринского элемента удалённого
    };

    std::shared_ptr<ExtractResult> binomialHeapExtractMin() {
        std::shared_ptr<ExtractResult> result(new ExtractResult);
        std::shared_ptr<Node> min = binomialHeapMinimum();
        std::shared_ptr<Node> headOfListOfChildren = min->child;
        std::shared_ptr<Node> buf;
        std::shared_ptr<Node> next = headOfListOfChildren->sibling;
        result->key = min->key;
        result->value = min->value;
        result->newPointerOnSibling = min;
        while (headOfListOfChildren != NIL) {
            headOfListOfChildren->parent = NIL;
            buf = headOfListOfChildren;
            headOfListOfChildren = next;
            next = headOfListOfChildren->sibling;
            headOfListOfChildren->sibling = buf;
        }
        min->child->sibling = NIL;
        min->child = min->sibling->child;
        min->key = min->sibling->key;
        min->degree = min->sibling->degree;
        min->sibling = min->sibling->sibling;
        BinomialHeap helper(NIL->key, absMin);
        helper.head = headOfListOfChildren;
        head = this->unionWith(helper)->head;
        return result;
    }

    void binomialHeapInsert(std::shared_ptr<Node> x) {
        x->parent = NIL;
        x->child = NIL;
        x->sibling = NIL;
        x->degree = 0;
        BinomialHeap helpHeap(NIL->key, absMin);
        helpHeap.head = x;
        this->head = this->unionWith(helpHeap)->head;
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
            K bufKey = y->key;
            V bufValue = y->value;
            y->key = z->key;
            y->value = z->value;
            z->key = bufKey;
            z->value = bufValue;
            y = z;
            z = y->parent.lock();
        }
        return oldKey;
    }

    std::shared_ptr<ExtractResult>binomialHeapDelete(std::shared_ptr<Node> node) {
        K key = binomialHeapDecreaseKey(node, absMin);
        std::shared_ptr<ExtractResult> result = binomialHeapExtractMin()->second;
        result->key = key;
        return result;
    }

    std::shared_ptr<Node> put(K key) {
        if (comp(NIL->key,key)) {
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
        if (comp(NIL->key,key)) {
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
        if (comp(infinity, NIL->key)) {
            return false;
        } else {
            NIL->key = infinity;
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
};

#endif // BINHEAP_H
