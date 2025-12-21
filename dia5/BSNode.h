#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
public:
    T elem;
    BSNode<T>* left;
    BSNode<T>* right;

    // Crea un nodo con un dato y sus hijos
    BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr) {
        this->elem = elem;
        this->left = left;
        this->right = right;
    }

    // Permite imprimir el nodo con cout
    friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
        out << bsn.elem;
        return out;
    }
};

#endif
