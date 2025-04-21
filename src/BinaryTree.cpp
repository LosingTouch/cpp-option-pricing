#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include <string>

// Constructor
template <typename T>
BinaryTree<T>::BinaryTree(int depth){
    _depth = depth;
    _tree.resize(_depth + 1);
    for (size_t i = 0; i < _tree.size(); i++)
        _tree[i].resize(i + 1);
}

// For an empty tree
template<typename T>
BinaryTree<T>::BinaryTree(): _depth(0){}

// Destructor
template <typename T>
BinaryTree<T>::~BinaryTree(){}

// Set Depth
template<typename T>
void BinaryTree<T>::setDepth(int depth){
    if(_depth > depth){ 
        // Shrink the tree if the new depth is smaller
        _depth = depth;
        _tree.resize(_depth + 1);
    }
    else{
        // Expand the tree if the new depth is larger
        _tree.resize(depth + 1);
        for(size_t i = _depth; i < _tree.size(); i++){
            _tree[i].resize(i+1);
        }
        _depth = depth;
    }
}

// Set Node Value
template<typename T>
void BinaryTree<T>::setNode(int id1, int id2, T NewValue){
    _tree[id1][id2] = NewValue;
}

// Get Node Value
template<typename T>
T BinaryTree<T>::getNode(int id1, int id2){
    return _tree[id1][id2];
}


// Display the tree
template<typename T>
void BinaryTree<T>::display(){
        for (int i = 0; i < _depth + 1; i++)
            {
                for (int j = 0; j <= i; j++)
                {
                    if (j != i)
                    {
                        std::cout << _tree[i][j] << "\t";
                    }
                    else
                    {
                        std::cout << _tree[i][j] << std::endl;
                    }
                }
            }
            std::cout << std::endl;
            for (size_t i = 0; i < _tree.size(); i++)
            {
                int space = _depth * 3 + 3 - 3 * i; // Calculate spacing for alignment

                if (i == _tree.size() - 1) // Print values for the last level
                {
                    for (int k = 0; k < space; k++)
                    {
                        std::cout << " ";
                    }

                    for (size_t j = 0; j < _tree[i].size(); j++)
                    {
                        long value = 0;
                        if (int(_tree[i][j]) == _tree[i][j])
                            value = std::to_string(int(_tree[i][j])).length();
                        else
                            value = std::to_string(int(_tree[i][j])*100).length() + 1;
                        switch (value)
                        {
                        case 1:
                            std::cout << "  " << _tree[i][j] << "   ";
                            break;
                        case 2:
                            std::cout << "  " << _tree[i][j] << "  ";
                            break;
                        case 3:
                            std::cout << "  " << _tree[i][j] << "  ";
                            break;

                        case 4:
                            std::cout << _tree[i][j] << "  ";
                            break;
                        default:
                                
                            std::cout << "Erreur" << " ";
                        }
                    }
                    std::cout << std::endl << std::endl;
                }
                else // Print values for other levels
                {
                    for (int k = 0; k < space; k++)
                    {
                        std::cout << " ";
                    }
                    for (size_t j = 0; j < _tree[i].size(); j++)
                    {
                        long value = 0;
                        if (int(_tree[i][j]) == _tree[i][j])
                            value = std::to_string(int(_tree[i][j])).length();
                        else
                            value = std::to_string(int(_tree[i][j])*100).length() + 1;
                        switch (value)
                        {
                        case 1:
                            std::cout << "  " << _tree[i][j] << "   ";
                            break;

                        case 2:
                            std::cout << "  " << _tree[i][j] << "  ";
                            break;

                        case 3:
                            std::cout << " " << _tree[i][j] << "  ";
                            break;
                        case 4:
                            std::cout << _tree[i][j] << "  ";
                            break;
                        default:
                            std::cout << "Erreur" << " ";
                        }
                    }
                    std::cout << std::endl;
                    for (int k = 0; k < space; k++)
                    {
                        std::cout << " ";
                    }
                    for (size_t j = 0; j < _tree[i].size(); j++)
                    {
                        std::cout << "/   \\ ";
                    }

                    std::cout << std::endl;
                }
            }
            std::cout << std::endl << std::endl;
}


template class BinaryTree<bool>;
template class BinaryTree<double>;
template class BinaryTree<int>;
