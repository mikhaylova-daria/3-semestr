#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <memory>
#include <limits>
namespace my {

    class exception: public std::exception {
    private:
        std::string _what;
    public:
        exception(const char * _what) throw() {
               this->_what = _what;
        }
        const char* what() const throw(){
            return _what.c_str();
        }
        ~exception() throw(){}
    };
}

template <typename T = int>
class SparseTable {
    std::vector<T> log_for_length;
    std::vector<T> array;
    std::vector<std::vector<T> > sparse_table;
    T (*func) (T, T);
    T neutral_element;
    int initial_size;
public:
    SparseTable(const std::vector<T> & arr, T (*_func)(T , T ), T _neutral_element) {
        neutral_element = _neutral_element;
        func = _func;
        array = arr;
        preproc_log();
        building_sparse_table();
    }

    T request(int l, int r) {
        if (l > r) {
            throw (my::exception("правый индекс меньше левого"));
        }
        if (l < 0 || r >= array.size()) {
            throw (my::exception("выход за границы массива"));
        }
        return func(sparse_table[log_for_length[r - l]][l], sparse_table[log_for_length[r - l]][r - (1 >> log_for_length[r - l]) + 1]);
    }

    void print() {
        for (int i = 0; i < sparse_table.size(); ++i) {
            for (int j = 0; j < sparse_table[i].size(); ++j) {
                std::cout<<sparse_table[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }

private:

    void building_sparse_table() {
        int n = (int)log2(array.size());
        sparse_table.resize(n + 1);
        for (int i = 0; i < array.size(); ++i) {
            sparse_table[0].push_back(array[i]);
        }
        for (int k = 1; k <= n; ++k) {
            for (int i = 0; (i + (1 << k)) <= array.size(); ++i) {
                sparse_table[k].push_back(func(sparse_table[k - 1][i], sparse_table[k - 1][i + (1 << (k - 1))]));
            }
        }
    }

    void preproc_log() {
        log_for_length.reserve(array.size()+1);
        log_for_length.push_back(0); //для длины 0
        log_for_length.push_back(0); // для длины 1
        for (int i = 2; i <= array.size(); ++i) {
            log_for_length[i] = log_for_length[i/2] + 1;
        }

    }


};


template <typename T>
T sum(T f, T s) {
    return f + s;
}

template <typename T>
T min_f (T f, T s) {
    if (f < s) {
        return f;
    } else {
        return s;
    }
}


#endif // SPARSE_TABLE_H
