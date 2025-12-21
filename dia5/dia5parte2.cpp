#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
};

// Ordenar rangos por start
bool operator<(const Range& a, const Range& b) {
    return a.start < b.start;
}

int main() {
    std::ifstream file("input.txt");     // abrir el archivo
    if (!file) {
        std::cerr << "Error al abrir el archivo\n";
        return 1;
    }

    std::vector<Range> ranges;
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

        ranges.push_back(Range(start, end)); // agrega rango al vector
    }

    // 2. Ordenar rangos por start
    std::sort(ranges.begin(), ranges.end());

    // 3. Fusionar rangos solapados
    std::vector<Range> merged;
    for (const auto& r : ranges) {
        if (merged.empty() || r.start > merged.back().end + 1) {
            // No se solapan, agrega nuevo
            merged.push_back(r);
        } else {
            // Fusionar con el último rango
            merged.back().end = std::max(merged.back().end, r.end);
        }
    }

    // 4. Contar todos los IDs frescos
    long long totalFresh = 0;
    for (const auto& r : merged) {
        totalFresh += (r.end - r.start + 1); // suma todos los elementos del rango
    }

    std::cout << "Total de IDs frescos: " << totalFresh << std::endl;

    return 0;
}
