#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <list>

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

class KMP {
    int pos_unique;
    unsigned long long int pos_text;
    std::string needle;
    std::vector<unsigned long long int> answer;

public:
    KMP(std::string _needle, char unique): pos_unique(_needle.length()){
        _needle.push_back(unique);
        needle = _needle;
        pos_text = 0;
    }

    ~KMP(){}

    std::vector<unsigned long long> search(std::istream& istr) {
        long int j = 0;
        char current_char;
        std::string buf = needle;
        for (int i = 0; i < pos_unique; ++i) {
            istr >> current_char;
            if (!istr.eof()) {
                buf.push_back(current_char);
            } else {
                return answer;
            }
        }
        std::vector<long int> pi(buf.length(), 0);
        j = 0;
        for (int i = 1; i < buf.length(); ++i) {
            while (j > 0 && buf.at(i) != buf.at(j)) {
                j = pi[j - 1];
            }
            if (buf.at(i) == buf.at(j)) {
                ++j;
            }
            pi[i] = j;
        }
        pos_text += pos_unique;
        while (!istr.eof()) {
            istr >> current_char;
            if (j == needle.length() - 1) {
                answer.push_back(pos_text - pos_unique + 1);
            }
            ++pos_text;
            if (!istr.eof()) {
                while (j > 0 && current_char != needle.at(j)) {
                    j = pi[j - 1];
                }
                if (current_char == needle.at(j)) {
                    ++j;
                }
            }
        }
        return answer;
    }

};


using namespace std;

int main()
{

    KMP kmp("aba", 'c');
    std::vector<unsigned long long int> answer = kmp.search(cin);
    std::cout<<std::endl;
    if (answer.size() == 0) {
        std::cout<<"not found"<<std::endl;
    } else {
        for (int i = 0; i < answer.size(); ++i) {
            std::cout<< answer[i]<<std::endl;
        }
    }
    return 0;
}

