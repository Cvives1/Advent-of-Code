## Advent of Code 2025 - Dia 7
### Compilar y ejecutar el archivo   

g++ -o dia7parte2 dia7parte2.cpp

Get-Content input.txt | ./dia7parte2.exe

Windows PowerShell

## **¿Por qué hemos elegido este problema? ¿Qué técnica hemos utilizado?**
Hemos elegido hacer el dia 7 porque hemos pensado que seria un caso donde podriamos aplicar con facilidad la tecnica de la programación dinámica.

En tanto la parte 1 como la parte 2, hemos utilizado una estructura constante para almacenar datos de cada iteracion distinta de un proceso recursivo, que, en el caso de estos ejercicios, es la matriz dp[][], donde se van almacenando valores booleanos de los lugares donde se producen splits para luego poder recontarlos en el caso de la 1ra parte o valores long long que representan en cuantas de las lineas temporales posibles ha pasado el haz por ese punto, en caso de la parte 2.

## **Descripción de la resolución del problema**
En ambas partes del trabajo utilizamos una funcion llamada F para parsear el problema:

### dia7parte1.cpp
```cpp
bool F(int i, int j) {
    if (i < 0 || i >= R || j < 0 || j >= C) return false; //si nos salimos del grid == falso
    if (dp[i][j] != -1) return dp[i][j]; //si ya se ha calculado esta celda se usa el resultado guardado

    bool reached = false;
    if (grid[i][j] == '^') {
        // Splitter: propagamos izquierda y derecha
        bool left  = F(i+1, j-1);
        bool right = F(i+1, j+1);
        reached = left || right;
        splits++; 
    } else if (i+1 < R) {
        reached = F(i+1, j);
    } else {
        reached = true; // última fila
    }

    dp[i][j] = reached ? 1 : 0; //se guarda resultado en la tabla
    return reached;
}
```


### dia7parte2.cpp
```cpp
long long F(int i, int j) {
    if (i >= R || j < 0 || j >= C) return 0;
    if (i == R-1) return 1;  
    if (dp[i][j] != -1) return dp[i][j]; //si ya se ha calculado esta celda, se usa el resultado

    long long ways = 0;
    if (grid[i][j] == '^') {
        ways += F(i+1, j-1); // se divide en iquierda y derecha
        ways += F(i+1, j+1);
    } else {
        ways += F(i+1, j);
    }
    dp[i][j] = ways; //se guarda el resultado
    return ways; 
}
```

En la 1ra parte se utiliza un booleano porque solamente hace falta saber si el haz pasa por ese punto en algun momento. En la 2da parte por otro lado se utiliza un long long porque lo que se busca es cuantas veces podria haber pasado por ese punto. 

### Sobre los mains
```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)){ 
        if (!line.empty()){ 
            grid.push_back(line);}}//se lee el input

    R = grid.size();
    C = grid[0].size();
    dp.assign(R, vector<int>(C, -1));

    int startCol = -1;
    for (int j = 0; j < C; j++){
        if (grid[0][j] == 'S'){
            startCol = j;}}

    if (startCol != -1 && R > 1){
        F(1, startCol);}

    cout << splits << "\n"; //se imprime el resultado
}
```

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) if (!line.empty()) grid.push_back(line); //se lee input

    R = grid.size();
    C = grid[0].size();
    dp.assign(R, vector<long long>(C, -1));

    int startCol = -1;
    for (int j = 0; j < C; j++){
        if (grid[0][j] == 'S'){ // Encontramos la columna inicial S
            startCol = j;}}

    long long total = F(1, startCol);  
    cout << total << "\n";
}
```

Ambos mains son practicamente iguales. En ambos casos se utiliza un bucle que se ocupa de encontrar la columna inicial S para poder setear la columna de inicio a la columna en la que se encuentre y en ambos casos se lee el input de la misma manera utilizando un while(getline()) junto a un if() que se asegura de que la linea no se encuentre vacia.

## **Otras alternativas**
Consideramos tambien la idea de intentar hacer este dia el advent of code utilizando arboles binarios, pero terminamos optando por programacion dinamica puesto a fue lo que pensamos seria mas simple a la hora de resolver y que seria un buen ejemplo de programacion dinamica para el proyecto. 

## **Valoración personal sobre lo aprendido**
Hemos aprendido un nuevo approach a la manera de utilizar programación dinámica. Inicialmente, la manera en la que resolvimos el ejercicio fue una que no se nos hubiese ocurrido, pero pensar un poco fuera de la caja nos llevo a poder resolver los problemas de manera limpia y simple. 


