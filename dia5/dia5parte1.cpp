#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "BSTree.h"

// Estructura para representar un rango [start, end]
struct Range {
    long long start;
    long long end;

    Range() {
        start = 0;
        end = 0;
    }

    Range(long long s, long long e) {
        start = s;
        end = e;
    }
    
    bool contains(long long x) const {
        return x >= start && x <= end;
    }
};

// Comparaciones necesarias para BST
bool operator<(const Range& a, const Range& b) { 
    if (a.start != b.start) {
        return a.start < b.start;
    }
    return a.end < b.end; 
}
bool operator>(const Range& a, const Range& b) {
    if (a.start != b.start) {
        return a.start > b.start;
    }
    return a.end > b.end;
}
bool operator==(const Range& a, const Range& b) {
    return a.start == b.start && a.end == b.end;
}

// Imprimir un rango [start-end]
std::ostream& operator<<(std::ostream &out, const Range &r) {
    out << "[" << r.start << "-" << r.end << "]";
    return out;
}

int main() {
    std::ifstream file("input.txt");     // abrir el archivo
    if (!file) {
        std::cerr << "Error al abrir el archivo\n";
        return 1;
    }

    BSTree<Range> tree;
    std::string line;

    // 1. Leer rangos
   while (std::getline(file, line)) {
        if (line.empty()) {
            break;  
        }

        long long start, end;
        if (sscanf(line.c_str(), "%lld-%lld", &start, &end) != 2) {
            std::cerr << "Linea de rango invalida: " << line << std::endl;
            continue;  // linea mal formada, sigue con la siguiente
        }

        tree.insert(Range(start, end));  // inserta el rango en el arbol
    }

    // 2. Leer IDs y contar los que estan en rangos
    long long freshCount = 0;
    while (std::getline(file, line)) {
        // limpia espacios al inicio y al final
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) continue; // linea vacia, ignora

        try {
            long long id = std::stoll(line);
            if (tree.containsRange(id))
                freshCount++;
        } catch (const std::exception &e) {
            std::cerr << "Línea de ID inválida: " << line << " (" << e.what() << ")\n";
            continue;
        }
    }

    std::cout << "Ingredientes frescos: " << freshCount << std::endl;
    return 0;
}
