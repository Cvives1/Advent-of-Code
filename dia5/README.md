## Advent of Code 2025 - Dia 5
### Compilar y ejecutar el archivo (linux)  
```cpp
g++ -o dia5parte1 dia5parte1.cpp  
./dia5parte1
```
```cpp
g++ -o dia5parte2 dia5parte2.cpp    
./dia5parte2
```
**Importante:** El código abre directamente "input.txt" con std::ifstream file("input.txt"), por lo que el .txt debe de llamarse input.txt obligatoriamente. 
## **¿Por qué hemos elegido este problema?** **¿Qué técnica hemos utilizado?**

Hemos elegido este problema porque es un excelente ejercicio de manejo de rangos numéricos, búsqueda eficiente y procesamiento de archivos. Permite practicar estructuras de datos como árboles binarios de búsqueda (BST), así como técnicas de ordenación y fusión de intervalos.

Para este día utilizamos:

- **Parte 1:** un BST para almacenar rangos de IDs y comprobar rápidamente si un ID concreto está dentro de algún rango.

- **Parte 2:** inicialmente se intentó usar un BST, pero surgieron problemas con la fusión de rangos encadenados y solapados, que podían dar resultados incorrectos. Por eso se optó por usar un vector de rangos.
---

## **Descripción de la resolución del problema**

Lo primero que hacemos es leer el archivo input.txt y almacenar cada línea como un rango [start, end].

### Lectura del input
```cpp
BSTree<Range> tree; // En la parte 2 se sustituye por std::vector<Range> ranges;
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

        tree.insert(Range(start, end));  // En la parte 2 se sustituye por ranges.push_back(Range(start, end));
    }
```

Con esto obtenemos todos los rangos de IDs frescos y los guardamos en la estructura elegida (BSTree en la parte 1 o vector en la parte 2).

### Parte 1 – Comprobar IDs frescos con BST

En dia5parte1.cpp usamos un árbol binario de búsqueda (BST) para almacenar los rangos y poder comprobar rápidamente si un ID dado está dentro de algún rango.
Pasos principales:

1. Insertar los rangos:
Cada rango [start, end] de la primera sección del archivo se inserta en el BST usando tree.insert(Range(start, end));.

4. Comprobar los IDs:
Para cada ID de la segunda sección del archivo, se verifica si está dentro de algún rango usando:
```cpp
if (tree.containsRange(id))
    freshCount++;
```
3. Contar y mostrar resultados:
Se incrementa el contador freshCount, visto en el codigo del paso anterior, cada vez que un ID está dentro de un rango, y al final se imprime el número total de IDs frescos encontrados según los rangos.

### Parte 2 – Contar todos los IDs frescos

En dia5parte2.cpp evitamos usar el BST y simplificamos el cálculo:

1. Ordenamos todos los rangos por "start".
```cpp
std::sort(ranges.begin(), ranges.end());
```

2. Fusionamos rangos que se solapan o son contiguos:
```cpp
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
```

3. Sumamos todos los IDs dentro de los rangos fusionados:
```cpp
long long totalFresh = 0;
for (const auto& r : merged) {
    totalFresh += (r.end - r.start + 1); // suma todos los elementos del rango
}
```

Resultado final: número total de IDs considerados frescos.

---


## **Otras alternativas**

La primera idea que tuvimos fue resolver este problema mediante una tabla hash, lo que para la parte 1 sería válido y eficiente. Sin embargo, al llegar a la parte dos nos dimos cuenta que hacerlo de esta manera era inviable, debido a que si los rangos son muy amplios y/o hubiesen muchos rangos distintos se ocuparía mucha memoria y no sería nada eficiente. Por esto descartamos resolverlo por tablas hash.

A continuacion se pensó en usar un árbol binario de búsqueda (BST) para toda la resolución, ya que permite mantener los rangos ordenados y hacer búsquedas rápidas. Funcionó bien en la parte 1, pero en la parte 2 surgieron problemas: al fusionar rangos solapados o contiguos que estaban en distintos nodos, algunos IDs podían contarse dos veces o perderse. 

Por este motivo, se optó finalmente por usar BST en la parte 1, y en la parte 2 un vector de rangos, ordenarlos y fusionarlos manualmente para garantizar un conteo exacto de todos los IDs frescos.

---


## **Valoración personal sobre lo aprendido**

Con esta práctica hemos reforzado:

- Lectura y procesamiento de archivos de texto.

- Uso de estructuras de datos: BST para búsqueda rápida y vector para fusión ordenada.

- Manejo de rangos y solapamiento de intervalos.

- Algoritmos de fusión de intervalos y conteo sin duplicados.

- Optimización de cálculos al evitar iterar sobre cada ID individual.
