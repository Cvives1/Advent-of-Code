## Advent of Code 2025 - Dia 11

## **¿Por qué hemos elegido este problema? ¿Qué técnica hemos utilizado?**
Hemos elegido este problema porque se trata de un caso claro de aplicación de **estructuras de datos avanzadas y algoritmos sobre grafos**.

En la **parte 1**, el objetivo era contar todos los caminos posibles desde un nodo inicial (`you`) hasta un nodo final (`out`).

En la **parte 2**, se añadió la condición de que cada camino debe pasar por dos nodos específicos (`dac` y `fft`).

Antes de nombrar las técnicas realizadas aclaro que hemos usado librerías que han sido realizadas en práctiicas, que son: **Dict.h**, **HashTable.h**, **List.h**, **ListLinked.h**, **Node.h** y **TableEntry.h**

Las técnicas para resolverlo que hemos utilizado son:

- **Tabla hash** para almacenar el grafo con acceso rápido a cada nodo.
- **Listas enlazadas (`ListLinked`)** para representar las salidas de cada nodo.
- **DFS (Depth First Search)** para recorrer todos los caminos posibles hasta el final.
- **Memorización** en la parte 2, para evitar recalcular caminos repetidos y manejar grandes grafos.

## **Descripción de la resolución del problema**
Para comenzar, hemos creado funciones para leer el input y construir el grafo con tabla hash y listas enlazadas.

### dia11parte1.cpp
En la parte 1, se contaban todos los caminos posibles desde `you` hasta `out` usando DFS sin memorización:
```cpp
int countPaths(HashTable<ListLinked<string>*>& graph, const string& node, const string& target) {
    if (node == target) return 1;

    int total = 0;
    ListLinked<string>* neighbors = graph[node];
    for (int i = 0; i < neighbors->size(); i++) {
        total += countPaths(graph, neighbors->get(i), target);
    }
    return total;
}
```

El grafo se construye leyendo cada línea del input, separando el nodo y sus vecinos:
```cpp
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
```

### dia11parte2.cpp
En la parte 2, se añadieron **memorización y control de estados** para verificar si cada camino pasa por `dac` y `fft`.

Se definió un `struct` para el estado del DFS:
```cpp
struct State {
    string node;
    bool hasDac;
    bool hasFft;

    bool operator==(const State &other) const {
        return node == other.node && hasDac == other.hasDac && hasFft == other.hasFft;
    }
};

struct StateHash {
    size_t operator()(const State& s) const {
        return hash<string>()(s.node) ^ hash<int>()(s.hasDac) ^ (hash<int>()(s.hasFft) << 1);
    }
};
```

El DFS con memorización devuelve un `long long` para evitar desbordes en grafos grandes:
```cpp
long long dfs(HashTable<ListLinked<string>*> &graph, const string &node, bool hasDac, bool hasFft,
              unordered_map<State,long long,StateHash> &memo) {
    if (node == "out") return (hasDac && hasFft) ? 1LL : 0LL;

    State st{node, hasDac, hasFft};
    if (memo.count(st)) return memo[st];

    bool newHasDac = hasDac || node == "dac";
    bool newHasFft = hasFft || node == "fft";

    long long count = 0;
    ListLinked<string>* outs;
    try {
        outs = graph.search(node);
    } catch(...) { return 0; }

    for(int i=0;i<outs->size();i++){
        string next = outs->get(i);
        count += dfs(graph, next, newHasDac, newHasFft, memo);
    }

    memo[st] = count;
    return count;
}
```

## **Otras alternativas**
Se exploró la idea de usar árboles pero el problema consiste en un grafo general con múltiples caminos posibles entre nodos, y los árboles binarios no permiten representar correctamente todos los caminos ni las conexiones múltiples de manera natural. Usarlos  no aportaría ninguna ventaja frente a la representación respecto a las tablas hash y listas enlazadas.

## **Valoración personal sobre lo aprendido**
Hemos aprendido a manejar tablas hash y listas enlazadas para representar grafos, aplicar DFS recursivo con memorización para contar caminos de forma eficiente, crear y usar structs como claves de hash, optimizar el código evitando recalcular caminos repetidos, y mejorar la comprensión de algoritmos sobre grafos y estructuras dinámicas, integrando teoría con práctica de implementación propia

