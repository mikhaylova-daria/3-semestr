#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <memory>
#include <limits>
#include "libr.h"
#include "sparse_table.h"
#include "FCB.h"
#include "treap.h"
#include "LCAtoRMQ.h"
using namespace std;
int dec(int i) {
    return i - 1;
}

int main()
{
//    std::vector<int> array;
//    for (int i = 64; i >= 0; --i) {
//        if (i % 17 == 0) {
//            array.push_back(i);
//        } else {
//            array.push_back(i);
//        }
//    }
////    array.push_back(4);
////    array.push_back(4);
////    array.push_back(4);
////    array.push_back(4);
////    array.push_back(2);
////    array.push_back(5);
////    array.push_back(9);
////    array.push_back(0);
////    array.push_back(7);
////    array.push_back(1);

//    SparseTable<int> sp(array, &min_f);
//    SparseTableFCB<int> sp2(array);
//  //  sp2.print();
//  //  cout <<"!"<< endl;

//    FCB fcb(array);
//    for (int i = 0; i < array.size(); ++i) {
//        for (int j = i; j < array.size(); ++j) {
//            if (fcb.query(i, j).first != sp.request(i, j)) {
//                std::cout<<"fail: "<<i<<" "<<j<<": "<<fcb.query(i, j).first  << " " <<sp.request(i, j)<<std::endl;
//            }
//           // std::cout<<"p"<<i<<" "<<j<<" ";
//            //std::cout<<sp2.request(i, j).first<<" "<< sp2.request(i, j).second<<std::endl;
//        }
//    }
//    //std::pair<int, int> p = fcb.query(0, 11);
//    //std::cout<<p.first<<" "<<p.second<<std::endl;

//    Treap<int, int> treap(&dec);
//    for (int i = 0; i < 100; ++i) {
//        treap.insert(i + 1, 100 - i);
//    }
    std::vector<int> pr;
    std::vector<int> keys;
    for (int i = 0; i < 50; ++i) {
        pr.push_back(i % 10);
        keys.push_back(i);
    }
//    Treap<int, int> treap(keys, pr, dec);
//    treap.print();
//    //treap.remove(2);
//    std::cout<<treap.find(15)->priority<<std::endl;
    std::shared_ptr<Treap<int, int> > treap_ptr(new Treap<int, int>(keys, pr, dec));
    LCA lca(treap_ptr);
    cout <<"end"<< endl;
    return 0;
}

