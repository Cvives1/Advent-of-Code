#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<int>> dp; // -1 = no visitado, 0 = falso, 1 = verdadero
int R, C;
long long splits = 0;

bool F(int i, int j) {
    if (i < 0 || i >= R || j < 0 || j >= C) return false;
    if (dp[i][j] != -1) return dp[i][j];

    bool reached = false;
    if (grid[i][j] == '^') {
        // Splitter: propagamos izquierda y derecha
        bool left  = F(i+1, j-1);
        bool right = F(i+1, j+1);
        reached = left || right;
        splits++; // solo se cuenta al llegar
    } else if (i+1 < R) {
        reached = F(i+1, j);
    } else {
        reached = true; // última fila
    }

    dp[i][j] = reached ? 1 : 0;
    return reached;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) if (!line.empty()) grid.push_back(line);

    R = grid.size();
    C = grid[0].size();
    dp.assign(R, vector<int>(C, -1));

    int startCol = -1;
    for (int j = 0; j < C; j++)
        if (grid[0][j] == 'S')
            startCol = j;

    if (startCol != -1 && R > 1)
        F(1, startCol);

    cout << splits << "\n";
}
