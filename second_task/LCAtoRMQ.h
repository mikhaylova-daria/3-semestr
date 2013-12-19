#ifndef LCATORMQ_H
#define LCATORMQ_H


class LCA {
    std::shared_ptr<Treap<int, int> > tree;
    std::vector<int> depth;
    std::vector<std::shared_ptr<Treap<int, int>::Node> > nodes;
    std::unordered_map<Treap<int, int>::Node *, int> indexes;
    std::shared_ptr<FCB> fcb;


    void dfs(std::shared_ptr<Treap<int, int>::Node> node, int& deep)
    {
        ++deep;
        nodes.push_back(node);
        depth.push_back(deep);
        indexes.insert(std::pair<Treap<int, int>::Node*, int>(node.get(), nodes.size() - 1));
        if (node->child_r != tree->NIL) {
            dfs(node->child_r, deep);
        }

        nodes.push_back(node);
        depth.push_back(deep);

        if (node->child_l != tree->NIL) {
            dfs(node->child_l, deep);
        }
        nodes.push_back(node);
        depth.push_back(deep);
        --deep;
    }

public:
    LCA(std::shared_ptr<Treap<int, int> > _tree): tree(_tree) {
        int deep = 0;
        dfs(tree->root, deep);
        fcb = std::shared_ptr<FCB>(new FCB(depth));
    }

    std::shared_ptr<Treap<int, int>::Node> request(std::shared_ptr<Treap<int, int>::Node> l, std::shared_ptr<Treap<int, int>::Node> r) {
        int index_l, index_r;
        if (indexes.find(l.get())->second < indexes.find(r.get()) ->second) {
            index_l = indexes.find(l.get())->second;
            index_r = indexes.find(r.get())->second;
        } else {
            index_l = indexes.find(r.get())->second;
            index_r = indexes.find(l.get())->second;
        }
        int pos = fcb->query(index_l, index_r).second;
        return nodes[pos];
    }
};

#endif // LCATORMQ_H
