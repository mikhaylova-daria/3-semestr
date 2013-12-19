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
    for (int i = 0; i < 200; ++i) {
        if (i % 17 == 0) {
            array.push_back(4);
        } else {
            array.push_back(3);
        }
    }
    array.push_back(4);
    array.push_back(4);
    array.push_back(4);
    array.push_back(4);
//    array.push_back(2);
//    array.push_back(5);
//    array.push_back(9);
//    array.push_back(0);
//    array.push_back(7);
//    array.push_back(1);

    SparseTable<int> sp(array, &min_f);
    SparseTableFCB<int> sp2(array);
  //  sp2.print();
  //  cout <<"!"<< endl;

    FCB fcb(array);
    for (int i = 0; i < array.size(); ++i) {
        for (int j = i; j < array.size(); ++j) {
            if (fcb.query(i, j).first != sp.request(i, j)) {
                std::cout<<"fail: "<<i<<" "<<j<<": "<<fcb.query(i, j).first  << " " <<sp.request(i, j)<<std::endl;
            }
           // std::cout<<"p"<<i<<" "<<j<<" ";
            //std::cout<<sp2.request(i, j).first<<" "<< sp2.request(i, j).second<<std::endl;
        }
    }
    //std::pair<int, int> p = fcb.query(0, 11);
    //std::cout<<p.first<<" "<<p.second<<std::endl;
    cout <<"end"<< endl;

    return 0;
}

