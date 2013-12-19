#ifndef FCB_H
#define FCB_H
#include "sparse_table.h"

std::pair<int, int> min_p (std::pair<int, int> f, std::pair<int, int> s) {
    if (f.first < s.first) {
        return f;
    } else {
        return s;
    }
}


class FCB {
    struct MaskTree {
        class Node {
        public:
            std::shared_ptr<Node> child_m1;
            std::shared_ptr<Node> child_p1;
            std::shared_ptr<Node> child_0;
            std::shared_ptr<SparseTableFCB<int> > sp_t;
            std::vector<int> norm_block;
        };
        std::shared_ptr<Node> root;
        std::weak_ptr<Node> current;
        std::vector<int> current_norm_block;
        MaskTree() {
            root = std::shared_ptr<Node>(new Node());
            current = root;
        }
        std::shared_ptr<SparseTableFCB<int> > in_begin() {
            current.lock() -> norm_block = current_norm_block;
            if (current.lock()->sp_t.use_count() == 0 && !current_norm_block.empty()) {
                current.lock()->sp_t = std::shared_ptr<SparseTableFCB<int> >(new SparseTableFCB<int> (current_norm_block));
            }
            std::shared_ptr<SparseTableFCB<int> > sp_t = current.lock()->sp_t;
            current = root;
            current_norm_block.clear();
            return sp_t;
        }

        void next(int i) {
            current_norm_block.push_back(i);
            if (i == -1) {
                if (current.lock()->child_m1.use_count() == 0) {
                    current.lock()->child_m1 = std::shared_ptr<Node>(new Node());
                }
                current = current.lock()->child_m1;
            } else if (i == 1) {
                if (current.lock()->child_p1.use_count() == 0) {
                    current.lock()->child_p1 = std::shared_ptr<Node>(new Node());
                }
                current = current.lock()->child_p1;
            } else if (i == 0) {
                if (current.lock()->child_0.use_count() == 0) {
                    current.lock()->child_0  = std::shared_ptr<Node>(new Node());
                }
                current = current.lock()->child_0;
            } else {
                throw (my::exception("непредвиденная ошибка"));
            }
        }
    };

    std::vector<int> array;
    std::vector<std::pair<int, int> > blocks_min;
    std::shared_ptr<SparseTable<std::pair<int, int> > >sp_t;
    std::vector<std::shared_ptr<SparseTableFCB<int> > > sp_t_for_inside_of_block;
    MaskTree mask_tree;
    bool flag_short = false;
    std::shared_ptr<SparseTableFCB<int> >sp_t_if_short;

public:
    FCB(std::vector<int> _array) {
        array = _array;
        blocks_split();
        if (!flag_short) {
            sp_t = std::shared_ptr<SparseTable<std::pair<int, int> > >(new SparseTable<std::pair<int, int> > (blocks_min, &min_p));
        }
    }


    std::pair<int, int> query(int l, int r) {
        int block_size = (int)(log2(array.size()) / 2);
        if (flag_short) {
            return sp_t_if_short->request(l, r);
        }
        int block_l = l / block_size;
        int block_r = r / block_size;
        std::pair<int, int> n1, n2, n3;
        if (block_l == block_r) {
            n1 = sp_t_for_inside_of_block[block_r]->request(l - block_l * block_size, r - block_size * block_r);
            n1.second += block_l * block_size;
            n1.first = array[n1.second];
            return n1;
        }
        n1 = sp_t_for_inside_of_block[block_l]->request(l - block_size * block_l, block_size - 1);
        n1.second += block_l * block_size;
        n1.first = array[n1.second];
        n3 = sp_t_for_inside_of_block[block_r]->request(0, r - block_size * block_r);
        n3.second += block_r * block_size;
        n3.first = array[n3.second];
        if (block_l == block_r - 1) {
            if (n1.first < n3.first) {
                return n1;
            } else {
                return n3;
            }
        }
        n2 = sp_t->request(block_l+1, block_r - 1);
        std::pair<int, int> min = n1;
        if (n2.first < min.first) {
            min = n2;
        }
        if (n3.first < min.first) {
            min = n3;
        }
        return min;
    }


private:
    void blocks_split() {
        int block_size = (int)(log2(array.size()) / 2);
        if (block_size < 2) {
            flag_short = true;
            sp_t_if_short = std::shared_ptr<SparseTableFCB<int> >(new SparseTableFCB<int>(array));
            return;
        }
        int i = 0;
        std::pair<int, int> min;
        while (i + block_size < array.size()) {
            min = std::pair<int, int> (array[i], i);
            for (int j = 0; j < block_size; ++j) {
                if (array[i + j] < min.first) {
                    min = std::pair<int, int>(array[i + j], i + j);
                }
                mask_tree.next(array[i + j] - array[i]);
            }
            sp_t_for_inside_of_block.push_back(mask_tree.in_begin());
            blocks_min.push_back(min);
            i = i + block_size;
        }
        int first;
        if (i < array.size()) {
            first = array[i];
        }
        while (i < array.size()) {
            min = std::pair<int, int> (array[i], i);
            if (array[i] < min.first) {
                min = std::pair<int, int>(array[i], i);
            }
            mask_tree.next(array[i] - first);
            ++i;
        }
        sp_t_for_inside_of_block.push_back(mask_tree.in_begin());
        blocks_min.push_back(min);
    }

};



#endif // FCB_H
