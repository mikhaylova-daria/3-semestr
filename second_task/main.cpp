#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <memory>
#include <limits>
#include "sparse_table.h"
#include "FCB.h"
using namespace std;

int main()
{
    std::vector<int> array;
    for (int i = 0; i < 20; ++i) {
        if (i % 3 == 0) {
            array.push_back(5);
        } else if (i % 4){
            array.push_back(4);
        }
    }
//    array.push_back(3);
//    array.push_back(8);
//    array.push_back(6);
//    array.push_back(4);
//    array.push_back(2);
//    array.push_back(5);
//    array.push_back(9);
//    array.push_back(0);
//    array.push_back(7);
//    array.push_back(1);

    SparseTable<int> sp(array, &min_f);
//    sp.print();
    cout <<sp.request(0, 0)<< endl;

    FCB fcb(array);
    std::cout<<fcb.query(0, 1).first;
    cout <<"end"<< endl;

    return 0;
}

