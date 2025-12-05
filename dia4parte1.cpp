#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> grid;
    string line;

    // Abrir archivo
    ifstream infile("input.txt"); // Cambia "entrada.txt" por el nombre de tu archivo
    if (!infile.is_open()) {
        cerr << "No se pudo abrir el archivo\n";
        return 1;
    }

    // Leer todas las líneas del archivo
    while (getline(infile, line)) {
        if (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
            line.pop_back();
        if (!line.empty())
            grid.push_back(line);
    }

    infile.close(); // Cerrar el archivo

    int h = grid.size();
    int w = grid.empty() ? 0 : grid[0].size();

    // Direcciones de los 8 vecinos
    int dirs[8][2] = {
        {-1,-1}, {-1,0}, {-1,1},
        {0,-1},          {0,1},
        {1,-1}, {1,0}, {1,1}
    };

    long long accesibles = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '@') {
                int vecinos = 0;

                // Contar vecinos '@'
                for (auto &d : dirs) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    if (ni >= 0 && ni < h && nj >= 0 && nj < w) {
                        if (grid[ni][nj] == '@')
                            vecinos++;
                    }
                }

                if (vecinos < 4)
                    accesibles++;
            }
        }
    }

    cout << accesibles << "\n";
    return 0;
}
