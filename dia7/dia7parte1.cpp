#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<int>> dp; // -1 = no visitado, 0 = falso, 1 = verdadero
int R, C;
long long splits = 0;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) if (!line.empty()) grid.push_back(line); //se lee el input

    R = grid.size();
    C = grid[0].size();
    dp.assign(R, vector<int>(C, -1));

    int startCol = -1;
    for (int j = 0; j < C; j++)
        if (grid[0][j] == 'S')
            startCol = j;

    if (startCol != -1 && R > 1)
        F(1, startCol);

    cout << splits << "\n"; //se imprime el resultado
}

