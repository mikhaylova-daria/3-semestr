#ifndef BM_H
#define BM_H
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>


class BM {
    std::string needle;
    std::vector<long int> postfixes;
    std::vector<long int> prefixes;
    std::unordered_map<char, std::vector<long int> > occurrence_char;

public:
    BM(std::string _needle):needle(_needle) {
        pre_processing();
    }

    ~BM(){}

    std::vector<unsigned long long> search(std::istream& istr) {
        std::vector<unsigned long long int> answer;
        char current_char_of_text = istr.get();
        long int current_pos_at_needle = needle.length() - 1;

        while (!istr.eof()) {


        }
        return answer;
    }

private:
    void pre_processing() {
        postfixes = postfix_fun();
        prefixes = prefix_fun();
        for (unsigned long i = 0; i < needle.length(); ++i) {
            std::unordered_map<char, std::vector<long int> > ::iterator itr = occurrence_char.find(needle.at(i));
            if (itr == occurrence_char.end()) {
                std::vector<long int> v;
                v.push_back(i);
                occurrence_char.insert(std::make_pair(needle.at(i), v));
            } else {
                itr->second.push_back(i);
            }
        }
        return;
    }

    std::vector<long int> postfix_fun() {
        std::vector<long int> pi (needle.length(), 0);
        for (long int i = needle.length() - 2; i >= 0; --i) {
            long int j = pi[i + 1];
            while (j > 0 && needle.at(i) != needle.at(needle.length() - j - 1)) {
                j = pi[needle.length() - j];
            }
            if (needle.at(i) == needle.at(needle.length() - j - 1)) {
                ++j;
            }
            pi[i] = j;
        }
        return pi;
    }

    std::vector<long int> prefix_fun() {
        std::vector<long int> pi (needle.length(), 0);
        for (long int i = 1; i < needle.length(); ++i) {
            long int j = pi[i - 1];
            while (j > 0 && needle.at(i) != needle.at(j)) {
                j = pi[j - 1];
            }
            if (needle.at(i) == needle.at(j)) {
                ++j;
            }
            pi[i] = j;
        }
        return pi;
    }

};

#endif // BM_H
