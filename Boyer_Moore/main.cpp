#include <iostream>
#include <BM.h>
using namespace std;

int main()
{
    BM a("abrbabr"); //abrbabr
    std::vector<unsigned long long int> answer = a.search(cin);
    if (answer.empty()) {
        std:: cout<<"not found"<<std::endl;
    } else {
        std:: cout<<"start:"<<std::endl;
        for (int i = 0; i < answer.size(); ++i) {
            std::cout<<answer[i]<<std::endl;
        }
    }
    return 0;
}

