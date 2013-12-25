#include <iostream>
#include <fstream>
#include "AhoCorasick.h"
using namespace std;

int main()
{
    std::vector<string> d;
    ifstream istr("/home/darya/OOP/Aho_Corasick/input.txt");
    int n;
    istr>>n;
    for (int i = 0; i < n; ++i) {
        std::string str;
        istr>>str;
        d.push_back(str);
    }
    AhoCorasick ah(d);
    std::vector<std::pair<std::string, unsigned long long> > answer = ah.search(istr);
    for (int i = 0; i < answer.size(); ++i) {
        cout<<answer[i].first<< " " << answer[i].second << std::endl;
    }
    return 0;
}

