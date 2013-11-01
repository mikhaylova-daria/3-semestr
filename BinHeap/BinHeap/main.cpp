#include <iostream>
#include <string>
#include "BinHeap.h"
using namespace std;

int main()
{
    BinomialHeap<string, int> a("z", "");
    a.put("aaa");
//    cout << a.head->key<<" ";
//    cout<< a.head->sibling->key<<endl;
//    cout<< a.head->child->key<<endl;
    a.put("a");
//    cout << a.head->key<<" ";
//    cout<< a.head->sibling->key<<endl;
//    cout<< a.head->child->key<<endl;

    a.put("ab");
//    cout << a.head->key<<" ";
//    cout<< a.head->sibling->key<<endl;
//    cout<< a.head->child->key<<endl;

    a.put("b");
//    cout << a.head->key<<" ";
//    cout<< a.head->sibling->key<<endl;
//    cout<< a.head->child->key<<endl;

    string x = a.binomialHeapMinimum()->getKey();
    cout << "min: "<<x << endl;
    cout <<"extract: "<< a.binomialHeapExtractMin()->key<<endl;
    x = a.binomialHeapMinimum()->getKey();
    cout << "new min: "<< x<< endl;
    a.binomialHeapDecreaseKey(a.binomialHeapMinimum(), "aa");
    cout<<"after decrease: "<<a.binomialHeapMinimum()->getKey()<<endl;
    return 0;
}

