#ifndef BM_H
#define BM_H
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <list>
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
    }

    ~BM(){}

    std::vector<unsigned long long> search(std::istream& istr) {
        std::vector<unsigned long long int> answer;
        std::list<char> substring_of_text;
        for (int i = 0; i < needle.length(); ++i) {
            if (istr.eof()) {
                return answer;
            }
            substring_of_text.push_back(istr.get());
        }
        long int current_offset_in_needle = needle.length() - 1;
        long int current_offset_in_text = 0;
        long int shift;
        std::list<char>::reverse_iterator itr_text = substring_of_text.rbegin();
        std::unordered_map<char, std::vector<long int> >::iterator itr;
        while (!istr.eof()) {
            while (current_offset_in_needle != 0) {
                if (needle.at(current_offset_in_needle) == *(itr_text)) {
                    --current_offset_in_needle;
                    ++itr_text;
                    if (current_offset_in_needle == 0) {
                        break;
                    }
                } else {
                    itr = occurrence_char.find(*itr_text);
                    if (itr == occurrence_char.end()) {
                        for (long int i = 0; i < needle.length(); ++i) {
                            if (!istr.eof()) {
                                substring_of_text.pop_front();
                                substring_of_text.push_back(istr.get());
                                ++current_offset_in_text;
                            } else {
                                return answer;
                            }
                        }
                        current_offset_in_needle = needle.length() - 1;
                        itr_text = substring_of_text.rbegin();
                    } else {
                        if (current_offset_in_needle == needle.length() - 1) {
                            shift = needle.length() - itr->second.back() - 1;
                        } else {
                            shift = suffix_offsets[needle.length() - current_offset_in_needle - 1];
                        }
                        for (long int i = 0; i < shift; ++i) {
                            if (!istr.eof()) {
                                substring_of_text.pop_front();
                                substring_of_text.push_back(istr.get());
                                ++current_offset_in_text;
                            } else {
                                return answer;
                            }
                        }
                        current_offset_in_needle = needle.length() - 1;
                        itr_text = substring_of_text.rbegin();
                    }
                }
            }
            answer.push_back(current_offset_in_text);
            substring_of_text.pop_front();
            substring_of_text.push_back(istr.get());
            ++current_offset_in_text;
            current_offset_in_needle = needle.length() - 1;
            itr_text = substring_of_text.rbegin();
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
