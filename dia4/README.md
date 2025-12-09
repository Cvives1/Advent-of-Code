## **¿Por qué hemos elegido este problema?** **¿Qué técnica hemos utilizado?**

Hemos elegido este problema porque es un buen ejercicio de procesamiento en rejillas (grids), detección de vecinos y simulación por pasos. Son tareas comunes en muchos desafíos de programación y permiten practicar manejo de archivos, vectores y algoritmos iterativos.

Para este día no utilizamos técnicas como divide y vencerás, sino que se aplican dos enfoques diferentes:

- **Parte 1:** un simple recorrido completo de la rejilla.

- **Parte 2:** una simulación iterativa, donde se va modificando el grid hasta que ya no cambie.
## **Descripción de la resolución del problema**

Lo primero que hacemos es leer el archivo input.txt y almacenar cada línea en un vector de strings llamado grid.

### Lectura del input
```
vector<string> grid;
string line;

ifstream infile("input.txt"); 
if (!infile.is_open()) {
    cerr << "No se pudo abrir el archivo\n";
    return 1;
}

while (getline(infile, line)) {
    if (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
        line.pop_back();
    if (!line.empty())
        grid.push_back(line);
}

infile.close();
```

Con esto obtenemos la rejilla completa y calculamos su alto h y su ancho w.
También definimos las 8 direcciones de búsqueda alrededor de cada casilla, para simular a los vecinos adyacentes (incluyendo diagonales).

### Direcciones de vecinos
```
int dirs[8][2] = {
    {-1,-1}, {-1,0}, {-1,1},
    {0,-1},          {0,1},
    {1,-1}, {1,0}, {1,1}
};
```

### Parte 1 – Contar '@' accesibles

En dia4parte1.cpp simplemente se recorre toda la rejilla una sola vez.

Para cada '@':

  1. Se cuentan cuántos vecinos '@' tiene.

  2. Si tiene menos de 4, se considera accesible y se suma al contador.
```
if (grid[i][j] == '@') {
    int vecinos = 0;

    for (auto &d : dirs) {
        int ni = i + d[0];
        int nj = j + d[1];
        if (ni >= 0 && ni < h && nj >= 0 && nj < w) {
            if (grid[ni][nj] == '@') vecinos++;
        }
    }

    if (vecinos < 4)
        accesibles++;
}
```

Resultado: solo se imprime cuántos '@' accesibles hay en la configuración original del mapa.

### Parte 2 – Eliminar accesibles en ciclos

En dia4parte2.cpp la lógica es más compleja porque es una simulación iterativa.

El proceso es:

  1. Buscar todos los '@' accesibles (los de menos de 4 vecinos)

Se guardan en un vector:
```
if (vecinos < 4)
    para_remover.emplace_back(i,j);
```
  2. Si no hay accesibles → fin
```
if (para_remover.empty())
    break;
```
  3. Eliminar todos los accesibles del ciclo
```
for (auto &p : para_remover) {
    grid[p.first][p.second] = '.';
}
total_removidos += para_remover.size();
```
  4. Repetir

La simulación continúa hasta que ya no quede ningún '@' con menos de 4 vecinos.

Resultado final: se imprime el número total de '@' eliminados a lo largo de todos los ciclos.
## **Otras alternativas**

No hemos explorado otras soluciones porque este problema se resuelve de manera óptima mediante recorrido por grid, conteo de vecinos y simulación por ciclos.
Técnicas comoBFS o DFS no aportan ventaja aquí, ya que no buscamos regiones conectadas sino reglas locales por celda.

## **Valoración personal sobre lo aprendido**

Con esta práctica hemos reforzado:

- Lectura y procesamiento de grids.

- Manejo correcto de índices y límites.

- Algoritmos basados en vecinos (muy habituales en simulaciones).

- Ciclos iterativos donde la matriz va cambiando paso a paso.

- Uso de vector<pair<int,int>> para almacenar coordenadas temporalmente.

Además, es un ejercicio que se parece a problemas reales como modelos celulares o simulaciones de vida artificial.
