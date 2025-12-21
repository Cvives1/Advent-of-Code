#ifndef BSTREE_H
#define BSTREE_H

#include <vector>
#include <ostream>
#include <stdexcept>
#include "BSNode.h"
#include <algorithm>

template <typename T>
class BSTree {
private:
    long long nelem;
    BSNode<T>* root;

    // Inserta un elemento en el arbol y une rangos si se solapan
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (!n) {
            return new BSNode<T>(e);
        }

        if (!(e.end < n->elem.start - 1 || e.start > n->elem.end + 1)) {
            // Si los rangos se tocan o se solapan, se unen
            n->elem.start = std::min(n->elem.start, e.start);
            n->elem.end   = std::max(n->elem.end, e.end);
            return n;
        }

        if (e < n->elem) {
            n->left  = insert(n->left, e);
        }
        else{             
            n->right = insert(n->right, e);
        }

        return n;
    }

    // Borra todo el arbol desde un nodo
    void delete_cascade(BSNode<T>* n) {
        if (!n) {
            return;
        }
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

    // Comprueba si un numero esta dentro de algun rango
    bool containsRange(BSNode<T>* node, long long id) const {
        if (!node){ 
            return false;
        }
        if (id >= node->elem.start && id <= node->elem.end){
            return true;
        }
        if (id < node->elem.start){ 
            return containsRange(node->left, id);
        }
        return containsRange(node->right, id);
    }

    // Recorre el arbol en orden y guarda los elementos
    void inorder(BSNode<T>* node, std::vector<T>& vec) const {
        if (!node){
            return;
        }
        inorder(node->left, vec);
        vec.push_back(node->elem);
        inorder(node->right, vec);
    }


public:
    BSTree() {
        nelem = 0;
        root = nullptr;
    }

    ~BSTree() { delete_cascade(root); }

    // Inserta un elemento en el arbol
    void insert(T e) { 
        root = insert(root, e); 
        nelem++;
    }

    // Comprueba si un numero esta en el arbol
    bool containsRange(long long id) const {
        return containsRange(root, id);
    }

    // Devuelve todos los elementos en orden
    std::vector<T> getAll() const {
        std::vector<T> vec;
        inorder(root, vec);
        return vec;
    }

};

#endif
