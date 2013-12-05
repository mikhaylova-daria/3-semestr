#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

namespace my {

class exception: public std::exception {
private:
    std::string _what;
public:
    exception(const char * _what) throw() {
           this->_what = _what;
    }
    const char* what() const throw(){
        return _what.c_str();
    }
    ~exception() throw(){}
};
}

class Shift_Or {
    std::vector<unsigned long long int> masks;
    std::list<unsigned long long int> table_equal;
    std::list<unsigned long long int> table_approximate_with_replacement;
    std::list<unsigned long long int> table_approximate_with_excision;
    std::list<unsigned long long int> table_approximate_with_insert;
    std::string needle;
    long long int max = 0;
    std::string text;
    std::string alphabet;
    std::unordered_map<char, unsigned long long int> alphabet_masks;

public:
    Shift_Or(std::string _needle, std::string alp) {
        if (_needle.length() == 1 || _needle.length() > 63) {
            throw (my::exception("Поиск для подстроки данной длины не осуществим"));
        }
        needle = _needle;
        alphabet = alp;
        for (unsigned short i = 0; i < needle.length(); ++i) {
            max += (1 << i);
        }
        pre_processing();
    }

    void pre_processing() {
        for (unsigned long i = 0; i < alphabet.size(); ++i) {
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

    std::vector<std::vector<unsigned long long > > search(std::istream& istr) {
        std::vector<unsigned long long> answer_equals;
        std::vector<unsigned long long> answer_approximate_with_replacement;
        std::vector<unsigned long long> answer_approximate_with_excision;
        std::vector<unsigned long long> answer_approximate_with_insert;
        unsigned long long int mask;
        mask = max;
        char current_char = istr.get();
        if (current_char == needle.at(0)) {
            mask = (max >> 1);
        }
        table_equal.push_back(mask);
        table_approximate_with_insert.push_back(((max >> 1) | alphabet_masks.find(current_char)->second));
        table_approximate_with_excision.push_back(((max >> 1) | alphabet_masks.find(current_char)->second) & (mask >> 1));
        table_approximate_with_replacement.push_back((max >> 1 | alphabet_masks.find(current_char)->second) & (max >> 1));
        if (needle.length() == 1) {
            if (table_equal.back() % 2 == 0) {
                answer_equals.push_back(1);
            }
            if (table_approximate_with_replacement.back() % 2 == 0 && table_equal.back() % 2 != 0) {
                    answer_approximate_with_replacement.push_back(1);
            }
        }
        bool flag = true;
        for (unsigned long long i = 2; flag; ++i) {
            current_char = istr.get();
            if (!istr.eof() && (alphabet_masks.find(current_char) != alphabet_masks.end())) {
                table_approximate_with_insert.push_back(table_equal.back()
                        & ((table_approximate_with_insert.back() >> 1) | alphabet_masks.at(current_char)));
                table_approximate_with_replacement.push_back((table_equal.back() >> 1) & ((table_approximate_with_replacement.back() >> 1) | alphabet_masks.at(current_char)));
                table_equal.push_back(((table_equal.back() >> 1) | alphabet_masks.at(current_char)));
                table_approximate_with_excision.push_back((table_equal.back() >> 1)
                                                          & ((table_approximate_with_excision.back() >> 1) | alphabet_masks.at(current_char)));
                table_approximate_with_excision.pop_front();
                table_approximate_with_insert.pop_front();
                table_approximate_with_replacement.pop_front();
                table_equal.pop_front();
                if (table_equal.back() % 2 == 0) {
                    answer_equals.push_back(i - needle.length() + 1);
                }
                if (table_approximate_with_insert.back() % 2 == 0) {
                    if (i != needle.length()) {
                        answer_approximate_with_insert.push_back(i - needle.length());
                    }
                }
                if (table_approximate_with_replacement.back() % 2 == 0 && table_equal.back() % 2 != 0) {
                    answer_approximate_with_replacement.push_back(i - needle.length() + 1);//
                }
                if (table_approximate_with_excision.back() % 2 == 0) {
                    answer_approximate_with_excision.push_back(i - needle.length() + 2);
                }
            } else {
                flag = false;
            }
        }
        std::vector<std::vector<unsigned long long int> > answer;
        answer.push_back(answer_equals);
        answer.push_back(answer_approximate_with_excision);
        answer.push_back(answer_approximate_with_insert);
        answer.push_back(answer_approximate_with_replacement);
        return answer;
    }
};


using namespace std;

int main()
{
    ifstream istr("/home/darya/OOP/Shift_or/input.txt");

    //Shift_Or so("abab", "acdbr");
    //Shift_Or so("ababa", "acdbr");
    Shift_Or so("abbb", "acdbr");
    std::vector<std::vector<unsigned long long> >answer; //= so.search(std::cin);
    answer = so.search(istr);
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

