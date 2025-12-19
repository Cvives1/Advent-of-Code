#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ListLinked.h"
#include "HashTable.h"
#include "TableEntry.h"

using namespace std;

int countPaths(HashTable<ListLinked<string>*>& graph, const string& node, const string& target) {
    if (node == target) return 1;

    int total = 0;
    ListLinked<string>* neighbors = graph[node];
    for (int i = 0; i < neighbors->size(); i++) {
        total += countPaths(graph, neighbors->get(i), target);
    }
    return total;
}

int main() {
    HashTable<ListLinked<string>*> graph(1000, 1000); 

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

    int totalPaths = countPaths(graph, "you", "out");
    cout << totalPaths << endl;

    return 0;
}
