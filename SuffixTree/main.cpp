#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "libr.h"


class SuffixTree {
    struct Node ;
    struct Edge;
    struct Node {
        std::weak_ptr<Node> suffix_link;
        Edge* parent_edge;
        std::unordered_map<char, std::shared_ptr<Edge> > next_chars;
    };

    struct Edge {
        std::shared_ptr<Node> child_node;
        std::weak_ptr<Node> parent_node;
        unsigned int start;
        unsigned int finish;
        bool isLeaf = true;
        int* finish_ptr;
        Edge() {
            std::shared_ptr<Node> ptr(new Node());
            child_node = ptr;
            child_node->parent_edge = this;
        }

        Edge(std::weak_ptr<Node> parent, int _start, int* _finish_ptr): finish_ptr(_finish_ptr),
                                                                               start(_start),
                                                                               parent_node(parent){
            std::shared_ptr<Node> ptr(new Node());
            child_node = ptr;
            child_node->parent_edge = this;
        }
        std::shared_ptr<Node> split(int index, const std::vector<char> &text) { // новое ребро дальше от root
            if (isLeaf) {
                this->finish = *(this->finish_ptr);
            }
          //  std::cout<<"!!!!!!!!!!!"<<this->start<<" "<<this->finish<<" "<<*(this->finish_ptr)<<std::endl;
            std::shared_ptr<Edge> new_edge(new Edge());
            new_edge->isLeaf = isLeaf;
            new_edge->start = start + index;
            new_edge ->finish_ptr = finish_ptr;
            new_edge->finish = finish;
            new_edge->child_node->next_chars = child_node->next_chars;
            child_node->next_chars.clear();
            finish = start + index - 1;
            new_edge->parent_node = child_node;
            child_node->next_chars.insert(std::pair<char, std::shared_ptr<Edge> > (text.at(new_edge->start - 1), new_edge));
            this->isLeaf = false;
//            std::cout<<"+++++++++"<<this->start<<" "<<this->finish<<" "<<*(this->finish_ptr)<<std::endl;
//            std::cout<<"--------"<<new_edge->start<<" "<<new_edge->finish<<" "<<*(this->finish_ptr)<<std::endl;
            return child_node;
        }
    };

    struct State {
        std::shared_ptr<Edge> current_edge;
        int index = 0;
        bool inRoot = true;
    };
    State current_pos;
    std::shared_ptr<Node> root;
    int finish_for_leafs = 0;
    std::shared_ptr<Edge> longest;
    std::vector<char> text;

public:
    SuffixTree() {
        std::shared_ptr<Node> ptr(new Node());
        root = ptr;
        root->suffix_link = root;
    }

    void append(char current_char) {
        text.push_back(current_char);
        ++finish_for_leafs;
        add_to_root(text.back());
        if (current_pos.inRoot) {
            std::weak_ptr<Edge> root_edge_since_cur_char = root->next_chars.find(text.back())->second;
            int finish = root_edge_since_cur_char.lock()->finish;
            if (root_edge_since_cur_char.lock()->isLeaf) {
                finish = finish_for_leafs;
                int length_of_suf = root_edge_since_cur_char.lock()->start - finish + 1;
                if (length_of_suf != 1) {
                    current_pos.current_edge = root_edge_since_cur_char.lock();
                    current_pos.index = 1;
                    current_pos.inRoot = false;
                }
            } else {
                current_pos.current_edge = root_edge_since_cur_char.lock();
                current_pos.index = 1;
                current_pos.inRoot = false;
            }
            return;
        }
       // std::cout<<text.at(current_pos.current_edge->start - 1)<<current_pos.current_edge->finish<<std::endl;
        if (!(current_pos.current_edge->isLeaf)) {
          //  std::cout<<current_pos.index + current_pos.current_edge->start - 1 <<"!!!"<<current_pos.current_edge->finish<<std::endl;
            if (current_pos.index + current_pos.current_edge->start - 1 != current_pos.current_edge->finish) {
                if (current_char == text.at(current_pos.current_edge->start + current_pos.index - 1)) {
                    ++current_pos.index;
                } else {
                    fork_from_edge();
                    check_current_pos();
                }
            } else {
                std::unordered_map<char, std::shared_ptr<Edge> >::iterator itr;
                itr = current_pos.current_edge->child_node->next_chars.find(current_char);
                if (itr == current_pos.current_edge->child_node->next_chars.end()) {
                    //fork from node
                    std::weak_ptr<Node> node = current_pos.current_edge->child_node;
                    std::shared_ptr<Edge> new_leaf(new Edge(node, text.size(), &finish_for_leafs));
                    node.lock()->next_chars.insert(std::pair<char, std::shared_ptr<Edge> > (current_char, new_leaf));
                    if (node.lock()->suffix_link.use_count() == 0) {
                        node.lock()->suffix_link = root;
                    }
                    node = node.lock()->suffix_link;
                    while (node != root) {
                        std::shared_ptr<Edge> new_leaf(new Edge(node, text.size(), &finish_for_leafs));
                        node.lock()->next_chars.insert(std::pair<char, std::shared_ptr<Edge> > (current_char, new_leaf));
                        node = node.lock()->suffix_link;
                    }
                    check_current_pos();
                } else {
                    current_pos.current_edge = itr->second;
                    current_pos.index = 1;// уже считали первую букву на ребре
                }
            }
        } else {
           //утв.: мы никогда не достигнем конца листа,
            //т.к. он увеличивается при добавлении элемента на 1, а мы двигаемся по его префикса на 1
            if (current_char == text.at(current_pos.current_edge->start + current_pos.index - 1)) {
                ++current_pos.index;
            } else {
                fork_from_edge();
                check_current_pos();
            }
        }
    }

    void check_current_pos() {
        std::weak_ptr<Edge> root_edge_since_cur_char = root->next_chars.find(text.back())->second;
        if (root_edge_since_cur_char.lock()->isLeaf) {
            root_edge_since_cur_char.lock()->finish = finish_for_leafs;
            int length_of_suf = root_edge_since_cur_char.lock()->start - root_edge_since_cur_char.lock()->finish + 1;
            if (length_of_suf > 1) {
                current_pos.current_edge = root_edge_since_cur_char.lock();
                current_pos.index = 1;
                current_pos.inRoot = false;
            } else {
                current_pos.inRoot = true;
            }
        } else {
            current_pos.current_edge = root_edge_since_cur_char.lock();
            current_pos.index = 1;
            current_pos.inRoot = false;
        }
    }

    void add_to_root(char current_char) {
        if (root->next_chars.find(current_char) == root->next_chars.end()) {
            root->next_chars.insert(std::pair<char, std::shared_ptr<Edge> > (current_char,
                                                                             std::shared_ptr<Edge> (new Edge(root, finish_for_leafs, &finish_for_leafs))));
        }
    }

    void fork_from_edge() {
        std::shared_ptr<Node> new_node =
                current_pos.current_edge->split(current_pos.index, text);
        std::shared_ptr<Edge> new_leaf(new Edge(new_node, text.size(), &finish_for_leafs));
        new_node->next_chars.insert(std::pair<char, std::shared_ptr<Edge> > (text.back(), new_leaf));
        char root_char = text.at(current_pos.current_edge->start - 1);
        std::weak_ptr<Node> other_branch_node = new_node->parent_edge->parent_node.lock()->suffix_link;
        if (other_branch_node != root) {
            while (other_branch_node != root) {
                std::weak_ptr<Edge> other_branch_edge = other_branch_node.lock()->next_chars.find(root_char)->second;
                new_node->suffix_link = other_branch_edge.lock()->split(current_pos.index, text);
                new_node = (new_node->suffix_link).lock();
                std::shared_ptr<Edge> new_leaf(new Edge(new_node, text.size(), &finish_for_leafs));
                new_node->next_chars.insert(std::pair<char, std::shared_ptr<Edge> > (text.back(), new_leaf));
                other_branch_node = other_branch_edge.lock()->parent_node.lock()->suffix_link;
            }
        }
        int index = current_pos.current_edge->finish - current_pos.current_edge->start;
        if (current_pos.current_edge->parent_node == root) {
            root_char = text.at(current_pos.current_edge->start); // вторая буква на ребре;
        } else {
            root_char = text.at(current_pos.current_edge->start - 1); // первая буква на ребре;
            index = current_pos.current_edge->finish - current_pos.current_edge->start + 1;
        }
        while (index > 0) {
            std::weak_ptr<Edge> other_branch_edge = other_branch_node.lock()->next_chars.find(root_char)->second;
            new_node->suffix_link = other_branch_edge.lock()->split(index, text);
            --index;
            root_char = text.at(other_branch_edge.lock()->start);
            new_node = (new_node->suffix_link).lock();
            std::shared_ptr<Edge> new_leaf(new Edge(new_node, text.size(), &finish_for_leafs));
            new_node->next_chars.insert(std::pair<char, std::shared_ptr<Edge> > (text.back(), new_leaf));
            other_branch_node = other_branch_edge.lock()->parent_node.lock()->suffix_link;//всегда root по-хорошему
        }


        // из текущей вершины шаг к предшествующей вершине, из неё по суффиксной стрелке вбок , вниз по нужной букве
        //на размер индекса
       // разветвление и т.д, пока не придём в root, из root виток по исходящим рёбрам
    }

    void print_tree() {
        std::vector<char> suffix;
        std::vector<int> pos;
        print(root, suffix, pos);
    }


    bool contains(const std::string& substr) {
        std::weak_ptr<Node> node = root;
        std::weak_ptr<Edge> edge;
        std::unordered_map<char, std::shared_ptr<Edge> >::iterator itr;
        int i = 0;
        for (; i < substr.size(); ++i) {
            itr = node.lock()->next_chars.find(substr.at(i));
            if (itr == node.lock()->next_chars.end()) {
                return false;
            }
            edge = itr->second;
            int length_edge = edge.lock()->finish - edge.lock()->start + 1;
            int j = 0;
            for (; j < length_edge; ++j) {
                if (i + j >= substr.size()) {
                    return true;
                }
                if (text.at(edge.lock()->start + j - 1) != substr.at(i + j)) {
                    return false;
                }
            }
            --j;
            i += j;
            node = edge.lock()->child_node;
        }
        return true;
    }

private:
    void print(std::weak_ptr<Node> node, std::vector<char>& suffix, std::vector<int>& pos) {
        std::unordered_map<char, std::shared_ptr<Edge> > ::iterator itr;
        Edge* edge;
        if (node != root) {
            edge = node.lock()->parent_edge;
        }
        for (itr = node.lock()->next_chars.begin(); itr != node.lock()->next_chars.end(); ++itr) {
            if (node == root) {
                if (itr->first != '\0') {
                    std::cout<<std::endl;
                    std::cout<<"char: "<<itr->first<<std::endl;
                }
            }
            if (itr->second->isLeaf) {
                itr->second->finish = finish_for_leafs;
            }
            int length = itr->second->finish - itr->second->start + 1;
            for (int i = itr->second->start - 1; i < itr->second->finish; ++i) {
                suffix.push_back(text.at(i));
                pos.push_back(i);
            }
            if (!itr->second->isLeaf) {
                print(itr->second->child_node, suffix, pos);
            } else {
                for (int i = 0; i < suffix.size(); ++i) {
                    std::cout<<suffix.at(i);
                }
//                std::cout<<std::endl;
//                for (int i = 0; i < suffix.size(); ++i) {
//                    std::cout<<pos.at(i) + 1;
//                }
                for (int i = 0; i < length; ++i) {
                    suffix.pop_back();
                    pos.pop_back();
                }
                std::cout<<std::endl;
            }
        }
        if (node != root) {
            int length = edge->finish - edge->start + 1;
            for (int i = 0; i < length; ++i) {
                suffix.pop_back();
                pos.pop_back();
            }
        }
    }

};




using namespace std;

int main()
{
    SuffixTree tree;
    char current;
    cin>> current;
    while (!cin.eof()) {
        tree.append(current);
        cin>>current;
    }
    tree.append('\0');
    std::cout<<tree.contains("abra")<<std::endl;
    tree.print_tree();
    return 0;
}
