#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ListLinked.h"
#include "HashTable.h"
#include "TableEntry.h"

using namespace std;
// función que cuenta los caminos de un nodo hasta un objetivo
int countPaths(HashTable<ListLinked<string>*>& graph, const string& node, const string& target) {
    if (node == target) return 1; //caso base

    int total = 0;
    ListLinked<string>* neighbors = graph[node]; //vecinos del nodo
    for (int i = 0; i < neighbors->size(); i++) { //se recorren las salidas del nodo
        total += countPaths(graph, neighbors->get(i), target);
    }
    return total;
}

int main() {
    HashTable<ListLinked<string>*> graph(1000, 1000); 
    // se lee el input
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string key;
        ss >> key;
        if (key.back() == ':') key.pop_back();

        ListLinked<string>* neighbors;
        try {
            neighbors = graph.search(key);
        } catch (...) {
            neighbors = new ListLinked<string>();
            graph.insert(key, neighbors);
        }

        string neighbor;
        while (ss >> neighbor) {
            neighbors->append(neighbor);
        }
    }
    //se cuentan los caminos de you hasta out
    int totalPaths = countPaths(graph, "you", "out");
    cout << totalPaths << endl; //se imprime el numero de los caminos posibles
    
    return 0;
}
