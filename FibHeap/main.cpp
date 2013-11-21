#include <iostream>
#include "libr.h"

using namespace std;

int main()
{
    FibHeap<int, int> a;
    FibHeap<int, int> b;
    a.insert(1, 2);
    a.insert(2, 3);
     a.insert(-2, 3);
    b.insert(3, 4);
    cout << a.extractMin().lock()->key;
    cout << "Hello World!" << endl;
    return 0;
}

