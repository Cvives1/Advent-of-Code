## Advent of Code 2025 - Dia 5
### Compilar y ejecutar el archivo (linux)  
```cpp
g++ -o dia5parte1 dia5parte1.cpp  
./dia5parte1
```
**Importante:** El código abre directamente "input.txt" con std::ifstream file("input.txt"), por lo que el .txt debe de llamarse input.txt obligatoriamente. 
## **¿Por qué hemos elegido este problema?** **¿Qué técnica hemos utilizado?**

Hemos elegido este problema porque es un buen ejercicio para trabajar con rangos numéricos, lectura de ficheros y búsquedas eficientes. Gracias a esto hemos podido implementar los árboles binarios de búsqueda (BST) para comprobar de forma rápida si un valor pertenece a alguno de los rangos dados.

Para este día utilizamos:

- **Parte 1:** un BST para almacenar rangos de IDs y comprobar rápidamente si un ID concreto está dentro de algún rango.

La Parte 2 no se entrega, ya que no se ha podido resolver correctamente utilizando árboles, como se explica más adelante.

---

## **Descripción de la resolución del problema**

Lo primero que hacemos es leer el archivo input.txt y almacenar cada línea como un rango [start, end].

### Lectura del input
```cpp
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

        tree.insert(Range(start, end));  
    }
```

Con esto obtenemos todos los rangos de IDs frescos y los guardamos en un árbol binario de búsqueda.

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

Inicialmente se intentó resolver también la Parte 2 utilizando un árbol binario de búsqueda, manteniendo los rangos ordenados y fusionándolos cuando fuese necesario. Sin embargo, este enfoque presentó problemas importantes.

En concreto, al trabajar con rangos solapados o contiguos almacenados en distintos nodos del árbol, la fusión correcta de estos rangos no siempre se realizaba bien. Esto provocaba que algunos IDs se contasen más de una vez o que otros se perdiesen, dando como resultado valores más altos o más bajos de lo esperado.

Finalmente, la Parte 2 se consiguió resolver correctamente utilizando vectores, ordenando los rangos y fusionándolos manualmente. No obstante, esta solución fue descartada, ya que el uso de vectores no estaba permitido como técnica para esta resolución.

---


## **Otras alternativas**

La primera idea que tuvimos fue resolver este problema mediante una tabla hash, lo que para la parte 1 parecia sería válido y eficiente. Sin embargo, al llegar a la parte dos nos dimos cuenta que hacerlo de esta manera era inviable, debido a que si los rangos son muy amplios y/o hubiesen muchos rangos distintos se ocuparía mucha memoria y no sería nada eficiente. Por esto descartamos resolverlo por tablas hash.

A continuacion se pensó en usar un árbol binario de búsqueda (BST) para toda la resolución, ya que permite mantener los rangos ordenados y hacer búsquedas rápidas. Funcionó bien en la parte 1, pero en la parte 2 surgieron problemas: al fusionar rangos solapados o contiguos que estaban en distintos nodos, algunos IDs podían contarse dos veces o perderse. 

Por estos motivos, se optó finalmente por usar BST en la parte 1, ya que es mas eficiente, y en la parte 2, aunque se obtuvo una solución correcta mediante vectores, decidimos descartarla por no adaptarse a los requerimientos.

---


## **Valoración personal sobre lo aprendido**

Esta práctica nos ha permitido profundizar en el uso de árboles binarios de búsqueda (BST), aprendiendo a insertar rangos y realizar búsquedas rápidas de manera eficiente. También se reforzó la lectura de archivos y el manejo de rangos numéricos, identificando las ventajas y limitaciones de los BST, especialmente en casos de fusión de rangos solapados.
