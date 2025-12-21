#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<long long>> dp;
int R, C;

long long F(int i, int j) {
    if (i >= R || j < 0 || j >= C) return 0;
    if (i == R-1) return 1;  // base: última fila → 1 timeline
    if (dp[i][j] != -1) return dp[i][j];

    long long ways = 0;
    if (grid[i][j] == '^') {
        ways += F(i+1, j-1);
        ways += F(i+1, j+1);
    } else {
        ways += F(i+1, j);
    }
    dp[i][j] = ways;
    return ways;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) if (!line.empty()) grid.push_back(line);

    R = grid.size();
    C = grid[0].size();
    dp.assign(R, vector<long long>(C, -1));

    int startCol = -1;
    for (int j = 0; j < C; j++)
        if (grid[0][j] == 'S')
            startCol = j;

    long long total = F(1, startCol);  // justo debajo de S
    cout << total << "\n";
}
