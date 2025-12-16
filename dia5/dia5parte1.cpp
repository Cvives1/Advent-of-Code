#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

//crea llaves unicas y las inserta en la tabla
int loadRanges(HashTable<string>& ranges) {
    string line;
    int count = 0;

    while (getline(cin, line)) {
        if (line.empty()){
          break;
        }

        string key = "r" + to_string(count++);
        ranges.insert(key, line);
    }
    return count; // número de rangos leídos
}

//si es fresco esta dentro del rango
bool isFreshId(long long id, HashTable<string>& ranges, int rangeCount) {
    for (int i = 0; i < rangeCount; i++) {
        string range = ranges.search("r" + to_string(i));

        size_t pos = range.find('-'); //se guarda la posicion del -
        long long start = stoll(range.substr(0, pos)); //primer numero
        long long end   = stoll(range.substr(pos + 1)); //segudno numero

        if (id >= start && id <= end) {
            return true;
        }
    }
    return false;
}


int main() {
    HashTable<string> ranges(300);

   
    int rangeCount = loadRanges(ranges);

    string line;
    int freshCount = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        long long id = stoll(line);
        if (isFreshId(id, ranges, rangeCount)) {
            freshCount++;
        }
    }

   
    cout << "Ingredientes frescos: " << freshCount << endl;
    return 0;
}
