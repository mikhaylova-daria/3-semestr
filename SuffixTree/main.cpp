#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>


class SuffixTree {
    struct Node {
        std::weak_ptr<Node> suffix_link;
        std::shared_ptr<Edge> longest;
        std::unordered_map<char, std::weak_ptr<Edge> > next_chars;
    };

    struct Edge {
        std::shared_ptr<Node> child_node = new Node();
        unsigned int start;
        unsigned int finish;
        bool isLeaf = true;
        int* finish_ptr;
        Edge(int _start, int* _finish_ptr): finish_ptr(_finish_ptr), start(_start){
        }
        Edge(int _start, std::weak_ptr<Edge> old_edge):  finish(old_edge.lock()->finish), start(_start){
            finish_ptr = old_edge.lock()->finish_ptr;
            isLeaf = old_edge.lock()->isLeaf;

        }
    };

    struct State {
        std::shared_ptr<Edge> current_edge;
        int index;
    };

    std::shared_ptr<Node> root;
    int finish_for_leafs = 0;
    std::shared_ptr<Edge> longest;
    std::vector<char> text;

public:
    SuffixTree() {
        root = new Node();
    }

    void append() {
        ++finish_for_leafs;
        if (root->next_chars.find(text.back()) == root.end()) {
            root->next_chars.insert(std::make_pair<char, std::shared_ptr<Node> >(text.back(), new Edge(finish_for_leafs, &finish_for_leafs)));
        }
    }

    void fork(std::weak_ptr<Edge> edge, int index) {
        std::shared_ptr<Edge> ptr_new_edge(edge.lock()->start - index, edge);
        std::shared_ptr<Edge> new_leaf(new Edge(text.size(), &finish_for_leafs));
        //новое ребро - листовое, старое ребро становится внутренним + появляется ещё один однобуквенный лист на развилке:
        edge.lock()->finish = index;
        edge.lock()->isLeaf = false;
        //развилка:
        edge.lock()->child_node->next_chars.insert(
                    std::make_pair<char, std::shared_ptr<Edge> >(text[edge.lock()->start - index], ptr_new_edge.lock);
        edge.lock()->child_node->next_chars.insert(std::make_pair<char, std::shared_ptr<Edge> >(text.back(), new_leaf));

    }
};




using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

