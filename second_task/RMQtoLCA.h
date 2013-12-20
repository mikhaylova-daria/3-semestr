#ifndef RMQTOLCA_H
#define RMQTOLCA_H
int dec(int i);
class RMQ {
    std::shared_ptr<Treap<int, int> > treap;
    std::vector<std::shared_ptr<Treap<int, int>::Node> > nodes;
    std::shared_ptr<LCA> lca;
    std::vector<int> array;
public:
    RMQ(std::vector<int> _array) {
        array = _array;
        std::vector<int> indexes;
        for (int i = 0; i < array.size();++i) {
            indexes.push_back(i);
        }
        treap = std::shared_ptr<Treap<int, int> >(new Treap<int, int>(indexes, array,  &dec, nodes));
        treap->print();
        lca = std::shared_ptr<LCA>(new LCA(treap));
    }
    std::pair<int, int> request(int l, int r) {
        int pos = lca->request(nodes[l], nodes[r])->key;
        return std::pair<int, int>(array[pos], pos);
    }
};

#endif // RMQTOLCA_H
