#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

pair<vector<pair<int,int>>, int> find_max_path(vector<vector<int>>& board, int start_x, int start_y, int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, 0));
    vector<vector<char>> path(n, vector<char>(m, ' '));

    dp[start_x][start_y] = 0;

    for (int j = start_y + 1; j < m; ++j) {
        dp[start_x][j] = dp[start_x][j - 1] + board[start_x][j];
        path[start_x][j] = 'R';
    }

    for (int i = start_x + 1; i < n; ++i) {
        dp[i][start_y] = dp[i - 1][start_y] + board[i][start_y];
        path[i][start_y] = 'D';
    }

    for (int i = start_x + 1; i < n; ++i) {
        for (int j = start_y + 1; j < m; ++j) {
            if (dp[i][j - 1] > dp[i - 1][j] || 
               (dp[i][j - 1] == dp[i - 1][j] && path[i][j - 1] == 'R')) {
                dp[i][j] = dp[i][j - 1] + board[i][j];
                path[i][j] = 'R';
            } else {
                dp[i][j] = dp[i - 1][j] + board[i][j];
                path[i][j] = 'D';
            }
        }
    }

    vector<pair<int, int>> path_coords;
    int i = n - 1, j = m - 1;
    path_coords.emplace_back(i, j);

    while (i != start_x || j != start_y) {
        if (path[i][j] == 'D') {
            i--;
        } else {
            j--;
        }
        path_coords.emplace_back(i, j);
    }

    reverse(path_coords.begin(), path_coords.end());
    return {path_coords, dp[n - 1][m - 1]};
}

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();

    vector<vector<int>> board (n, vector<int> (m));
    int start_x = -1, start_y = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            string s;
            cin >> s;
            if (s == "S") {
                board[i][j] = 0;
                start_x = i;
                start_y = j;
            } else {
                board[i][j] = stoi(s);
            }
        }
    }

    auto [path, coins] = find_max_path(board, start_x, start_y, n, m);

    cout << "Path:\n";
    for (const auto& [x, y] : path) {
        cout << "(" << x << "," << y << ") ";
    }

    cout << "\nCoins: " << coins << endl;

    return 0;
}
