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

    std::vector<unsigned long long > search_equal(std::string text) {
        std::vector<unsigned long long> answer;
        unsigned long long int mask;
        mask = std::numeric_limits<unsigned long long int>::max();
        if (text.at(0) == needle.at(0)) {
            mask = (max ^ (1 << (needle.length() - 1)));
            table_equal.push_back(mask);
        }
        table_equal.push_back(mask);
        for (unsigned long long i = 1; i < text.length(); ++i) {
            char current_char = text.at(i);
            unsigned long long int mask_for_current_char = ((table_equal.back() >> 1) | alphabet_masks.at(current_char));
            table_equal.push_back(mask_for_current_char);
            if (mask_for_current_char % 2 == 0) {
                answer.push_back(i - needle.length() + 2);
            }
        }
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
    std::vector<unsigned long long> answer = so.search_equal("abracadabra");
    for (int i = 0; i < answer.size(); ++ i) {
        cout<<answer.at(i)<<std::endl;
    }
    return 0;
}

