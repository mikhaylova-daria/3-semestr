#ifndef TREAP_H
#define TREAP_H

template <typename K, typename P,  typename Compare = std::less<P>, typename V = int>
class Treap {
    struct Node {
        std::shared_ptr<Node> child_l;
        std::shared_ptr<Node> child_r;
        std::weak_ptr<Node> parent;
        K key;
        P priority;
        V value;
        Node(K _key, P _priority, V _value = 0): value(_value), key(_key), priority(_priority) {
        }
    };
    Compare comp;
    std::shared_ptr<Node> root = NIL;
    static std::shared_ptr<Node> NIL;
    K (*dec) (K);
    //std::shared_ptr<Node> current;
    std::shared_ptr<Node> last_added;

public:

    Treap(K (*_dec)(K)): dec(_dec) {
    }

    Treap (std::vector<K> keys, std::vector<P> priorities, K (*_dec)(K)): dec(_dec) {
        root = std::shared_ptr<Node>(new Node(keys[0], priorities[0]));
        std::shared_ptr<Node> last_added = root;
        root->parent = root;
        std::shared_ptr<Node> current;
        for (int i = 1; i < keys.size(); ++i) {
            current = std::shared_ptr<Node>(new Node(keys[i], priorities[i]));
            if (!comp(last_added->priority, priorities[i])) {
                current->parent = last_added;
                last_added->child_r = current;
            } else {
                std::shared_ptr<Node> x = last_added->parent.lock();
                while (x != root && comp(x->priority, current->priority)) {
                    x = x->parent.lock();
                }
                if (x != root) {
                    current->child_l = x->child_r;
                    current->child_l->parent = current;
                    current->parent = x;
                    x->child_r = current;
                } else {
                    current->child_l = root;
                    root -> parent = current;
                    root = current;
                }
            }
        }
    }


    std::shared_ptr<Node> insert(K key, P priority ,V value = 0) {
        std::shared_ptr <Node> new_node = std::shared_ptr<Node>(new Node(key, priority,  value));
        std::shared_ptr <Node> t1, t2;
        split(root, key, t1, t2);
        root = merge(t1, new_node);
        root = merge(root, t2);
        return new_node;
    }

    void remove(K key) {
        std::shared_ptr<Node> t1, t2, t3;
        split(root, dec(key), t1, t2);
        split(t2, key, t2, t3);
        root = merge(t1, t3);
    }

    std::shared_ptr<Node> find(K key) {
        std::shared_ptr<Node> result = NIL;
        std::shared_ptr<Node> t1, t2, t3;
        split(root, dec(key), t1, t2);
        split(t2, key, t2, t3);
        if (t2 != NIL) {
            result = t2;
        }
        t1 = merge(t1, t2);
        root = merge(t1, t3);
        return result;
    }


private :
    std::shared_ptr<Node> merge(std::shared_ptr<Node> a_root, std::shared_ptr<Node> b_root) {
        if (a_root == NIL || b_root == NIL)
            return (a_root != NIL) ? a_root : b_root;
        if (!comp(a_root->priority, b_root->priority)) {
            a_root->child_r = merge(a_root->child_r, b_root);
            return a_root;
        } else {
            b_root->child_l = merge(a_root, b_root->child_l);
            return b_root;
        }
    }

    void split(std::shared_ptr<Node> start, K key, std::shared_ptr<Node> &a, std::shared_ptr<Node> &b) {
        if (start == NIL) {
            a = NIL;
            b = NIL;
        } else if (start->key <= key) {
            split(start->child_r, key, start->child_r, b);
            a = start;
        } else {
            split(start->child_l, key, a, start->child_l);
            b = start;
        }
    }
};

template <typename K, typename P, typename Compare, typename V>
std::shared_ptr<typename Treap<K, P, Compare, V>::Node> Treap<K, P, Compare, V>::NIL = nullptr;
#endif // TREAP_H
