#include <iostream>
#include "sparse_table.h"
using namespace std;

int main()
{
    std::vector<int> array;
    for (int i = 0; i < 10; ++i) {
        //array.push_back(i);
    }
    array.push_back(3);
    array.push_back(8);
    array.push_back(6);
    array.push_back(4);
    array.push_back(2);
    array.push_back(5);
    array.push_back(9);
    array.push_back(0);
    array.push_back(7);
    array.push_back(1);
    SparseTable<int> sp(array, &min_f, -1);
    sp.print();
    cout <<sp.request(1, 0)<< endl;
    return 0;
}

