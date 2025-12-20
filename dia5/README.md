## **¿Por qué hemos elegido este problema?** **¿Qué técnica hemos utilizado?**

Hemos elegido este problema porque es un excelente ejercicio de manejo de **rangos numéricos**, búsqueda eficiente y procesamiento de archivos. Permite practicar estructuras de datos como **árboles binarios de búsqueda** (BST), así como técnicas de **ordenación y fusión de intervalos**.

Para este día utilizamos:

- **Parte 1:** un **BST** para almacenar rangos de IDs y comprobar rápidamente si un ID concreto está dentro de algún rango.
- **Parte 2:** ordenación y **fusión de rangos** usando un vector, evitando duplicados y sumando los IDs frescos de manera eficiente.

---

## **Descripción de la resolución del problema**

Lo primero que hacemos es leer el archivo `input.txt` y almacenar cada línea como un rango `[start, end]`.

### Lectura del input
```cpp
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
