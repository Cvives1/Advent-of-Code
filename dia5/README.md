## **¿Por qué hemos elegido este problema?** **¿Qué técnica hemos utilizado?**

Hemos elegido este problema porque es un excelente ejercicio de manejo de rangos numéricos, búsqueda eficiente y procesamiento de archivos. Permite practicar estructuras de datos como árboles binarios de búsqueda (BST), así como técnicas de ordenación y fusión de intervalos.

Para este día utilizamos:

- **Parte 1:** un BST para almacenar rangos de IDs y comprobar rápidamente si un ID concreto está dentro de algún rango.

- **Parte 2:** ordenación y fusión de rangos usando un vector, evitando duplicados y sumando los IDs frescos de manera eficiente.

---

## **Descripción de la resolución del problema**

Lo primero que hacemos es leer el archivo input.txt y almacenar cada línea como un rango [start, end].

### Lectura del input
```
std::vector<Range> ranges;
std::string line;

std::ifstream file("input.txt");
if (!file) {
    std::cerr << "Error al abrir el archivo\n";
    return 1;
}

while (std::getline(file, line)) {
    if (line.empty()) break; // Separación entre secciones

    long long start, end;
    if (sscanf(line.c_str(), "%lld-%lld", &start, &end) != 2) {
        std::cerr << "Línea inválida: " << line << "\n";
        continue;
    }
    ranges.push_back(Range(start, end));
}
```

Con esto obtenemos todos los rangos de IDs frescos y los guardamos en un vector de Range.

### Parte 1 – Comprobar IDs frescos con BST

En dia5parte1.cpp usamos un árbol binario de búsqueda (BST) para almacenar los rangos y poder comprobar rápidamente si un ID dado está dentro de algún rango:

1. Insertamos cada rango en el BST.

2. Para cada ID de la segunda sección del archivo, verificamos si existe en algún rango usando containsRange(id).

3. Contamos los IDs frescos.
```
if (tree.containsRange(id))
    freshCount++;
```

Resultado: se imprime el número de IDs frescos encontrados según los rangos.

### Parte 2 – Contar todos los IDs frescos

En dia5parte2.cpp evitamos usar el BST y simplificamos el cálculo:

1. Ordenamos todos los rangos por start.
```
std::sort(ranges.begin(), ranges.end());
```

2. Fusionamos rangos que se solapan o son contiguos:
```
std::vector<Range> merged;
for (const auto& r : ranges) {
    if (merged.empty() || r.start > merged.back().end + 1) {
        merged.push_back(r);
    } else {
        merged.back().end = std::max(merged.back().end, r.end);
    }
}
```

3. Sumamos todos los IDs dentro de los rangos fusionados:
```
long long totalFresh = 0;
for (const auto& r : merged) {
    totalFresh += (r.end - r.start + 1);
}
```

Resultado final: número total de IDs considerados frescos, sin duplicados.

---


## **Otras alternativas**

La primera idea que tuvimos fue resolver este problema mediante una tabla hash, lo que para la parte 1 sería válido y eficiente. Sin embargo, al llegar a la parte dos nos dimos cuenta que hacerlo de esta manera era inviable, debido a que si los rangos son muy amplios y/o hubiesen muchos rangos distintos se ocuparía mucha memoria y no sería nada eficiente. Por esto descartamos resolverlo por tablas hash.

---


## **Valoración personal sobre lo aprendido**

Con esta práctica hemos reforzado:

- Lectura y procesamiento de archivos de texto.

- Uso de estructuras de datos: BST para búsqueda rápida y vector para fusión ordenada.

- Manejo de rangos y solapamiento de intervalos.

- Algoritmos de fusión de intervalos y conteo sin duplicados.

- Optimización de cálculos al evitar iterar sobre cada ID individual.
