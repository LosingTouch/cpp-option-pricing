#pragma once
#include <vector>

template <typename T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    BinaryTree(int depth);
    BinaryTree();
    ~BinaryTree();
    void setDepth(int depth);
    void setNode(int id1, int id2, T NewValue);
    T getNode(int id1, int id2);
    void display();
};