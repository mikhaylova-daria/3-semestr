#ifndef BM_H
#define BM_H
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
long int min(const long int &first, const long int& second) {
    if (first < second) {
        return first;
    } else {
        return second;
    }
}

class BM {
    std::string needle;
    std::vector<long int> postfixes;
    std::vector<long int> prefixes;
    std::vector<long int> suffix_offsets;
    std::unordered_map<char, std::vector<long int> > occurrence_char;


public:
    BM(std::string _needle):needle(_needle) {
        pre_processing();
        for (int i = 0; i < suffix_offsets.size(); ++i) {
            std::cout<<suffix_offsets[i]<<std::endl;
        }
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
        prefixes = prefix_fun(needle);
        suffix_offsets = suffix_offsets_function();
        suffix_offsets_function();
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


    std::vector<long int> suffix_offsets_function() {
        std::vector<long int> suff(needle.length() + 1, needle.length() - prefixes.back());
        suff[0] = 1;
        for (long int i = 1; i < needle.length(); ++i) {
            long int j = postfixes[i];
            suff[j]  = min(suff[j], i - postfixes[i] + 1);
        }
        return suff;
    }

    std::vector<long int> postfix_fun() {
        std::vector<long int> pi (needle.length(), 0);
        std::string needle_reverse(needle.rbegin(), needle.rend());
        return prefix_fun(needle_reverse);
    }

    std::vector<long int> prefix_fun(std::string str) {
        std::vector<long int> pi (str.length(), 0);
        long int j = 0;
        for (long int i = 1; i < str.length(); ++i) {
            while (j > 0 && str.at(i) != str.at(j)) {
                j = pi[j - 1];
            }
            if (str.at(i) == str.at(j)) {
                ++j;
            }
            pi[i] = j;
        }
        return pi;
    }

};

#endif // BM_H
