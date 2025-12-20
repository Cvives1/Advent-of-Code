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
    Range() : start(0), end(0) {}
    Range(long long s, long long e) : start(s), end(e) {}
};

// Ordenar rangos por start
bool operator<(const Range& a, const Range& b) {
    return a.start < b.start;
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error al abrir el archivo\n";
        return 1;
    }

    std::vector<Range> ranges;
    std::string line;

    // Leer rangos del archivo
    while (std::getline(file, line)) {
        if (line.empty()) break; // Separación entre secciones

        long long start, end;
        if (sscanf(line.c_str(), "%lld-%lld", &start, &end) != 2) {
            std::cerr << "Línea inválida: " << line << "\n";
            continue;
        }
        ranges.push_back(Range(start, end));
    }

    // Ordenar rangos por start
    std::sort(ranges.begin(), ranges.end());

    // Fusionar rangos solapados
    std::vector<Range> merged;
    for (const auto& r : ranges) {
        if (merged.empty() || r.start > merged.back().end + 1) {
            // No se solapan
            merged.push_back(r);
        } else {
            // Fusionar con el último rango
            merged.back().end = std::max(merged.back().end, r.end);
        }
    }

    // Contar todos los IDs frescos
    long long totalFresh = 0;
    for (const auto& r : merged) {
        totalFresh += (r.end - r.start + 1);
    }

    std::cout << "Total de IDs frescos: " << totalFresh << std::endl;

    return 0;
}