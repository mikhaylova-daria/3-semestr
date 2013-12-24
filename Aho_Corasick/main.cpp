#include <iostream>
#include "AhoCorasick.h"
using namespace std;

int main()
{
    std::vector<string> d;
    while (cin) {
        std::string str;
        cin>>str;
        d.push_back(str);
    }
    AhoCorasick ah(d);
    cout << "Hello World!" << endl;
    return 0;
}

