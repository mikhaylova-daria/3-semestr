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

int min(int f, int s) {
    if (f < s) {
        return f;
    } else {
        return s;
    }
}

int max(int f, int s) {
    if (f > s) {
        return f;
    } else {
        return s;
    }
}


template <typename T = int>
class SegmentTree {
    std::vector<T> tree;
    std::vector<T> array;
    T (*func) (T, T);
    T neutral_element;
    int initial_size;
public :
    SegmentTree(const std::vector<T> & arr, T (*_func)(T , T ), T _neutral_element) {
        neutral_element = _neutral_element;
        initial_size = arr.size();
        func = _func;
        array = arr;
        if (array.size() != (1 << (int)log2(arr.size()))) {
            while (array.size() != (2 << (int)log2(arr.size()))) {
                array.push_back(neutral_element);
            }
        }
        tree.resize(array.size() * 2 - 1);
        building(0, 0 , array.size());
//        for (int i = 0; i < tree.size(); ++i) {
//            std::cout<<tree[i]<<std::endl;
//        }
    }

    T search(int l, int r) throw (my::exception) {
        if (r < l) {
            throw (my::exception("Правый индекс меньше левого"));
        }
        if (r >= initial_size || l < 0) {
            throw (my::exception("Выход за границы массива"));
        }
        return (this->_search(0, 0, array.size() - 1, l, r));
    }

    void update (int pos, T new_val) throw (my::exception) {
        if (pos >= initial_size || pos < 0) {
            throw  (my::exception("Выход за границы массива"));
        }
        _update(0, 0, array.size() - 1, pos, new_val);
    }

private:

    void building(int i, int l, int r) {
        if (l == r) {
            return;
        }
        if (r - l == 1) {
           tree[i] = array[l];
        } else {
           int mid = (l + r) / 2;
           building(2 * i + 1, l, mid);
           building(2 * i + 2, mid, r);
           tree[i] = func(tree[2 * i + 1], tree[2 * i + 2]);
        }
    }

    T _search (int i, int tree_l, int tree_r, int l, int r) {
        if (l > r)
            return neutral_element;
        if (l == tree_l && r == tree_r)
            return tree[i];
        int mid = (tree_l + tree_r) / 2;
        return func(_search(i*2 + 1, tree_l, mid, l, min(r,mid)), _search(i*2+2, mid + 1, tree_r, max(l, mid+1), r));
    }

    void _update (int i, int tree_l, int tree_r, int pos, T new_val) {
        if (tree_l == tree_r)
            tree[i] = new_val;
        else {
            int mid = (tree_l + tree_r) / 2;
            if (pos <= mid)
                _update (i * 2 + 1, tree_l, mid, pos, new_val);
            else
                _update (i * 2 + 2, mid + 1, tree_r, pos, new_val);
            tree[i] = func(tree[i * 2 + 1], tree[i * 2 + 2]);
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

using namespace std;

int main()
{
    std::vector<int> a;
    for (int i = 0; i < 10; ++i) {
        a.push_back(i);
    }
    SegmentTree<int> tree(a, &sum, 0);
    tree.update(4, 10);
    std::cout<<tree.search(0, 9)<<std::endl;
    SegmentTree<int> tree1(a, &min_f, std::numeric_limits<int>::max());
    tree1.update(4, -1);
    try {
        std::cout<<tree1.search(-1, 6)<<std::endl;
    } catch (my::exception e) {
        std::cout<< e.what()<<std::endl;
    }
    std::cout<<tree1.search(6, 9)<<std::endl;

    return 0;
}

