#include <iostream>
#include <fstream>
#include <string>
#include "BinHeap.h"
using namespace std;

int main()
{

    std::ofstream fout("/home/darya/OOP/BinHeap/output.txt");

    std::ifstream fin("/home/darya/OOP/BinHeap/input.txt");
    BinomialHeap<int> a(10000,  -10000);
    fin>>a;
    //std::cout<<a;
    int n;
//    std::shared_ptr<BinomialHeap<int>::Node>  node = a.put(123);
//    a.binomialHeapDecreaseKey(node, 23);
//    std::cout<<a<<endl;
//    cin >> n;
//    a.binomialHeapExtractMin();
//    a.binomialHeapDecreaseKey(node, 10);
//    std::cout<<a<<endl;
//    cin >> n;
//    a.binomialHeapDecreaseKey(node, 1);
//    a.binomialHeapDelete(node);
    list<shared_ptr<BinomialHeap<int>::Node > > l = a.getNodesList();
    list<shared_ptr<BinomialHeap<int>::Node > >::iterator itr;
    for (itr = l.begin(); itr != l.end(); ++itr) {
        std::cout << *itr;
    }
    cout << "\n";
    while (!a.isEmpty()) {
        std::cout<<a<<endl;
        a.binomialHeapExtractMin();
        cout << "------------------------------------------------------------------------\n";
        cin >> n;
    }

    fout.close();
    fin.close();
    return 0;
}

