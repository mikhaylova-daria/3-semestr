#ifndef AHOCORASICK_H
#define AHOCORASICK_H
#include <unordered_map>
#include <vector>
#include <list>
#include <memory>

class AhoCorasick {
    struct Node {
        std::unordered_map<char, std::shared_ptr<Node> > sons;
        int pos_pattern_in_dictionary = -1;
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
    int pos_in_text = 0;
    std::vector<std::pair <std::string, unsigned long long> > answer;
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
            node.lock()->pos_pattern_in_dictionary = i;
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
            std::cout << node.lock()->term<< ":" <<std::endl;

            for (itr_child = node.lock()->sons.begin(); itr_child != node.lock()->sons.end(); ++itr_child) {
                if (itr_child->second->parent.lock() == root) {
                    itr_child->second->suf_link = root;
                    itr_child->second->good_link = root;
                } else {
                    itr_child->second->suf_link = jump(itr_child->second->parent.lock()->suf_link, itr_child->second->term);
                    itr_child->second->good_link = good_jump(itr_child->second);
                }
                std::cout<<itr_child->second->term<<" "<<itr_child->second->parent.lock()->term;
                std::cout<<"("<<itr_child->second->suf_link.lock()->term<<")";
                std::cout<<"<"<<itr_child->second->good_link.lock()->term<<">";
std::cout<<std::endl;
                gray.push_back(itr_child->second);
            }
        }

    }

    std::weak_ptr<Node> jump(std::weak_ptr<Node> node, char c) {
        std::unordered_map<char, std::shared_ptr<Node> > ::iterator itr;
        itr = node.lock()->sons.find(c);
        if (itr != node.lock()->sons.end()) {
            std::cout<<"*"<<std::endl;
            return itr->second;
        } else {
            if (node.lock() == root) {
                return root;
            }
            return jump(node.lock()->suf_link, c);
            std::cout<<"@"<<std::endl;
        }
    }

    std::weak_ptr<Node> good_jump(std::weak_ptr<Node> node) {
        if (node.lock()->suf_link.lock()->is_finish) {
           // std::cout<<"yes"<<std::endl;
            return node.lock()->suf_link;
        } else {
           // return node.lock()->suf_link.lock()->good_link;
            return good_jump(node.lock()->suf_link);
        }
    }

    std::vector<std::pair <std::string, unsigned long long> > search(std::istream& istr) {
        answer.clear();
        std::weak_ptr<Node> node = root;
        char current_char;
        istr >> current_char;
        ++pos_in_text;
        std::unordered_map<char, std::shared_ptr<Node> >::iterator itr;
        while ((!istr.eof())) {
            itr = node.lock()->sons.find(current_char);
            while (itr == node.lock()->sons.end()) {
                node = node.lock()->suf_link;
                //write(node);
                itr = node.lock()->sons.find(current_char);
//                std::cout<<"!!"<<std::endl;
                if ((node.lock() == root)
                        && (itr == node.lock()->sons.end())) {
                    istr >> current_char;
                    ++pos_in_text;
                }
            }
            node = itr->second;
            istr >> current_char;
            ++pos_in_text;
            write(node);
        }
        return answer;
    }

    void write(std::weak_ptr<Node> node) {
        if (node.lock()->is_finish) {
            answer.push_back(std::pair <std::string, unsigned long long>
                         (dictionary[node.lock()->pos_pattern_in_dictionary],
                         pos_in_text - dictionary[node.lock()->pos_pattern_in_dictionary].size()));
            std::cout<<"new"<<node.lock()->pos_pattern_in_dictionary<<std::endl;
        }
            while (node.lock() != root) {
                node = node.lock()->good_link;
                if (node.lock()->pos_pattern_in_dictionary > -1) {
                    answer.push_back(std::pair <std::string, unsigned long long>
                                    (dictionary[node.lock()->pos_pattern_in_dictionary],
                                    pos_in_text - dictionary[node.lock()->pos_pattern_in_dictionary].size()));
                }
            }

    }


};
#endif // AHOCORASICK_H
