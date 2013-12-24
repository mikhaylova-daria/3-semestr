#ifndef AHOCORASICK_H
#define AHOCORASICK_H
#include <unordered_map>
#include <vector>
#include <list>
#include <memory>

class AhoCorasick {
    struct Node {
        std::unordered_map<char, std::shared_ptr<Node> > sons;
        std::vector<int> pos_pattern_in_dictionary;
        bool is_finish = false;
        std::weak_ptr<Node> suf_link;
        std::weak_ptr<Node> good_link;
        std::weak_ptr<Node> parent;
        char term;
        Node() {;}
        Node(std::weak_ptr<Node> _parent, char _term): parent(_parent), term(_term) {
        }
    };

    std::vector<std::string> dictionary;
    std::shared_ptr<Node> root;

public:
    AhoCorasick(std::vector<std::string> _dictionary): dictionary(_dictionary) {
        building_trie();
        suf_linking();
    }

    void building_trie() {
        root = std::shared_ptr<Node>(new Node(root, '/0'));
        root->is_finish = true;
        root->suf_link = root;
        std::unordered_map<char, std::shared_ptr<Node> >::iterator itr;
        std::weak_ptr<Node> node = root;
        for (int i = 0; i < dictionary.size(); ++i) {
            for (int j = 0; j < dictionary[i].size(); ++j) {
                itr = node.lock()->sons.find(dictionary[i][j]);
                if (itr == node.lock()->sons.end()) {
                    node.lock()->sons.insert(std::pair<char, std::shared_ptr<Node> >
                                             (dictionary[i][j], std::shared_ptr<Node>(new Node(node, dictionary[i][j]))));
                    itr = node.lock()->sons.find(dictionary[i][j]);
                }
                node = itr -> second;
            }
            node.lock()->is_finish = true;
            node.lock()->pos_pattern_in_dictionary.push_back(i);
            node = root;
        }
    }

    void suf_linking() {
        std::list<std::weak_ptr<Node> > gray;
        gray.push_back(root);
        while (!gray.empty()) {
            std::weak_ptr<Node> node = gray.front();
            gray.pop_front();
            std::unordered_map<char, std::shared_ptr<Node> >:: iterator itr_child;
            for (itr_child = node.lock()->sons.begin(); itr_child != node.lock()->sons.end(); ++itr_child) {

                itr_child->second->suf_link = jump(itr_child->second->parent.lock()->suf_link, itr_child->second->term);
                itr_child->second->good_link = good_jump(itr_child->second);
                gray.push_back(itr_child->second);
            }
        }
    }

    std::weak_ptr<Node> jump(std::weak_ptr<Node> node, char c) {
        if (node.lock()->term == c) {
            return node;
        } else {
            if (node.lock() == root) {
                return root;
            }
            jump(node.lock()->parent, c);
        }
    }

    std::weak_ptr<Node> good_jump(std::weak_ptr<Node> node) {
        if (node.lock()->suf_link.lock()->is_finish) {
            return node.lock()->suf_link;
        } else {
            return node.lock()->good_link;
           // good_jump(node.lock()->suf_link);
        }
    }
};
#endif // AHOCORASICK_H
