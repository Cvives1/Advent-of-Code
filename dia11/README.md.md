## Advent of Code 2025 - Dia 11

## **¿Por qué hemos elegido este problema? ¿Qué técnica hemos utilizado?**
Hemos elegido este problema porque se trata de un caso claro de aplicación de **estructuras de datos avanzadas y algoritmos sobre grafos**.

En la **parte 1**, el objetivo era contar todos los caminos posibles desde un nodo inicial (`you`) hasta un nodo final (`out`).

En la **parte 2**, se añadió la condición de que cada camino debe pasar por dos nodos específicos (`dac` y `fft`).

Para resolverlo hemos utilizado:

- **Hash tables** para almacenar el grafo con acceso rápido a cada nodo.
- **Listas enlazadas (`ListLinked`)** para representar las salidas de cada nodo.
- **DFS (Depth First Search)** para recorrer todos los caminos posibles.
- **Memoización** en la parte 2, para evitar recalcular caminos repetidos y manejar grandes grafos.

## **Descripción de la resolución del problema**
Para comenzar, hemos creado funciones para leer el input y construir el grafo con hash tables y listas enlazadas.

### dia11parte1.cpp
En la parte 1, se contaban todos los caminos posibles desde `you` hasta `out` usando DFS sin memoización:
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
En la parte 2, se añadieron **memoización y control de estados** para verificar si cada camino pasa por `dac` y `fft`.

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

El DFS con memoización devuelve un `long long` para evitar desbordes en grafos grandes:
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

### Llamada principal
- **Parte 1:**
```cpp
int totalPaths = countPaths(graph, "you", "out");
cout << totalPaths << endl;
```
- **Parte 2:**
```cpp
unordered_map<State,long long,StateHash> memo;
long long totalPaths = dfs(graph, "svr", false, false, memo);
cout << totalPaths << endl;
```

## **Otras alternativas**
Se podría haber utilizado `unordered_map<string, vector<string>>` para el grafo, pero usar nuestras propias estructuras (`HashTable` y `ListLinked`) demuestra dominio de la implementación de estructuras de datos.

Se descartó recorrer el grafo sin memoización en la parte 2, ya que habría sido demasiado lento.

## **Valoración personal sobre lo aprendido**
Hemos aprendido:

- Manejo de **hash tables y listas enlazadas** para representar grafos.
- Uso de **DFS recursivo y memoización** para contar caminos eficientemente.
- Creación y uso de **structs como claves de hash**.
- Optimización de código para evitar recalcular caminos repetidos.
- Mejora de comprensión de algoritmos sobre grafos y estructuras dinámicas.

