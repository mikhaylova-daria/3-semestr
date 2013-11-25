#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>

class Shift_Or {
    std::vector<unsigned long long int> masks;
    std::vector<unsigned long long int> table_equal;
    std::vector<unsigned long long int> table_approximate_with_replacement;
    std::vector<unsigned long long int> table_approximate_with_excision;
    std::vector<unsigned long long int> table_approximate_with_insert;
    std::string needle;
    long long int max = 0;
    std::string text;
    std::string alphabet;
    std::unordered_map<char, unsigned long long int> alphabet_masks;

public:
    Shift_Or(std::string _needle, std::string alp) {
        needle = _needle;
        alphabet = alp;
        for (unsigned short i = 0; i < needle.length(); ++i) {
            max  += (1 << i);
        }
        pre_processing();
    }

    void pre_processing() {
        for (unsigned long i = 0; i < alphabet.length(); ++i) {
            unsigned long long mask = max;
            for (unsigned short j = 0; j < needle.length(); ++j) {
                if (needle.at(j) == alphabet.at(i)) {
                    mask = mask & (max ^ (1 << (needle.length() - j - 1)));
                }
            }
            alphabet_masks.insert(std::make_pair(alphabet.at(i), mask));
        }
        return;
    }

    std::vector<std::vector<unsigned long long > > search(std::string text) {
        std::vector<unsigned long long> answer_equals;
        std::vector<unsigned long long> answer_approximate_with_replacement;
        std::vector<unsigned long long> answer_approximate_with_excision;
        std::vector<unsigned long long> answer_approximate_with_insert;
        unsigned long long int mask;
        mask = max;
        if (text.at(0) == needle.at(0)) {
            mask = (max ^ (1 << (needle.length() - 1)));
        }
        table_equal.push_back(mask);
        table_approximate_with_insert.push_back(mask);
        table_approximate_with_excision.push_back(mask >> 1);
        for (unsigned long long i = 1; i < text.length(); ++i) {
            char current_char = text.at(i);
            table_approximate_with_insert.push_back(table_equal.back()
                    & ((table_approximate_with_insert.back() >> 1) | alphabet_masks.at(current_char)));
            table_equal.push_back(((table_equal.back() >> 1) | alphabet_masks.at(current_char)));
            table_approximate_with_excision.push_back((table_equal.back() >> 1)
                                                      & ((table_approximate_with_excision.back() >> 1) | alphabet_masks.at(current_char)));
            if (table_equal.back() % 2 == 0) {
                answer_equals.push_back(i - needle.length() + 2);
                if (i - needle.length() + 2 > 1) {
                    answer_approximate_with_insert.push_back(i - needle.length() + 1);
                }
            }
            if (table_approximate_with_insert.back() % 2 == 0 && table_equal.back() % 2 != 0) {
                if (i - needle.length() + 1 > 0) {
                    answer_approximate_with_insert.push_back(i - needle.length() + 1);
                }
            }
            if (table_approximate_with_excision.back() % 2 == 0 && table_equal.back() % 2 != 0) {
                answer_approximate_with_excision.push_back(i - needle.length() + 3);
            }

        }
        std::vector<std::vector<unsigned long long int> > answer;
        answer.push_back(answer_equals);
        answer.push_back(answer_approximate_with_excision);
        answer.push_back(answer_approximate_with_insert);
        answer.push_back(answer_approximate_with_replacement);
        return answer;
    }



//    friend std::ostream& operator << (std::ostream& ostr, std::shared_ptr<Node> const & node)  {
//        ostr << node->key << " (" << node->value << ") ";
//        return ostr;
//    }

//    friend std::istream& operator >>  (std::istream& istr, BinomialHeap<K, V, Compare> & heap){
//        istr >>  >> value;
//        while (!istr.eof()) {
//            last = heap.put(key, value);
//            istr >> key >> value;
//        }
//        return istr;
//    }

    void read (std::istream& istr) {
        istr.get();
    }
};


using namespace std;

int main()
{
    Shift_Or so("abra", "acdbr");
    std::vector<std::vector<unsigned long long> >answer = so.search("aabrararaabbra");
    std::cout<<"equal:\n";
    for (int i = 0; i < answer[0].size(); ++ i) {
        cout<<answer[0][i]<<std::endl;
    }
    std::cout<< "with_excision:\n";
    for (int i = 0; i < answer[1].size(); ++ i) {
        cout<<answer[1][i]<<std::endl;
    }
    std::cout<< "with_insert:\n";
    for (int i = 0; i < answer[2].size(); ++ i) {
        cout<<answer[2][i]<<std::endl;
    }
    std::cout<< "with_repl:\n";
    for (int i = 0; i < answer[3].size(); ++ i) {
        cout<<answer[3][i]<<std::endl;
    }
    return 0;
}

