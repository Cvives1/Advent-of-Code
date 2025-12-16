#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    // Constructor
    ListLinked() : first(nullptr), n(0) {}

    // Destructor
    ~ListLinked() {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
    }

    // Tamaño de la lista
    int size() const override { return n; }

    // Comprueba si está vacía
    bool empty() const override { return n == 0; }

    // Obtiene el elemento en la posición pos
    T get(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
        Node<T>* aux = first;
        for (int i = 0; i < pos; i++) aux = aux->next;
        return aux->data;
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        return get(pos);
    }

    // Inserta elemento e en la posición pos
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("Posición inválida!");
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* aux = first;
            for (int i = 0; i < pos - 1; i++) aux = aux->next;
            aux->next = new Node<T>(e, aux->next);
        }
        n++;
    }

    // Elimina y devuelve el elemento en la posición pos
    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
        Node<T>* aux = first;
        T val;
        if (pos == 0) {
            val = first->data;
            first = first->next;
            delete aux;
        } else {
            for (int i = 0; i < pos - 1; i++) aux = aux->next;
            Node<T>* toDelete = aux->next;
            val = toDelete->data;
            aux->next = toDelete->next;
            delete toDelete;
        }
        n--;
        return val;
    }

    // Busca elemento e y devuelve su posición
    int search(T e) override {
        Node<T>* aux = first;
        int pos = 0;
        while (aux != nullptr) {
            if (aux->data == e) return pos;
            aux = aux->next;
            pos++;
        }
        return -1;
    }

    // Agrega elemento al final
    void append(T e) { insert(n, e); }

    // Agrega elemento al principio
    void prepend(T e) { insert(0, e); }

    // Sobrecarga del operador << para imprimir
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "List => [\n";
        Node<T>* aux = list.first;
        while (aux != nullptr) {
            out << "  " << aux->data << "\n";
            aux = aux->next;
        }
        out << "]";
        return out;
    }
};

#endif // LISTLINKED_H
