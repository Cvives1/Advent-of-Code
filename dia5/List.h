#ifndef LIST_H
#define LIST_H

template <typename T>
class List {
public:
    // Destructor virtual
    virtual ~List() {}

    // Métodos abstractos (puros) que deben implementarse en las clases derivadas
    virtual int size() const = 0;          // devuelve el número de elementos
    virtual bool empty() const = 0;        // indica si la lista está vacía
    virtual void insert(int pos, T e) = 0; // inserta el elemento e en la posición pos
    virtual T get(int pos) = 0;            // devuelve el elemento en la posición pos
    virtual T remove(int pos) = 0;         // elimina y devuelve el elemento en la posición pos
    virtual int search(T e) = 0;           // devuelve el índice del elemento e, o -1 si no está
};

#endif // LIST_H

