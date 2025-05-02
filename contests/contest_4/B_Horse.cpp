#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

vector<ll> get_neighbors(ll i, ll j, ll n) {
    vector<pair<ll, ll>> moves = {
        {-2, -1}, {-2, 1},
        {-1, -2}, {-1, 2},
        {1, -2}, {1, 2},
        {2, -1}, {2, 1}
    };
    
    vector<ll> neighbors;
    for (const auto& move : moves) {
        ll new_i = i + move.first;
        ll new_j = j + move.second;
        if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < n) {
            neighbors.push_back(new_i * n + new_j);
        }
    }
    sort(neighbors.begin(), neighbors.end()); 
    return neighbors;
}

vector<vector<ll>> build_adj_list(ll n) {
    vector<vector<ll>> adj_list(n * n);
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            adj_list[i * n + j] = get_neighbors(i, j, n);
        }
    }
    return adj_list;
}

bool hamiltonian_path(ll current, vector<ll>& path, vector<bool>& visited, const vector<vector<ll>>& adj_list) {
    path.push_back(current);
    visited[current] = true;

    if (path.size() == adj_list.size()) {
        return true;
    }

    for (ll neighbor : adj_list[current]) {
        if (!visited[neighbor]) {
            if (hamiltonian_path(neighbor, path, visited, adj_list)) {
                return true;
            }
        }
    }

    path.pop_back();
    visited[current] = false;
    return false;
}

void print_matrix(const vector<ll>& path, ll n) {
    vector<vector<ll>> board(n, vector<ll>(n, -1));
    for (ll step = 0; step < path.size(); ++step) {
        ll i = path[step] / n;
        ll j = path[step] % n;
        board[i][j] = step;
    }
    for (const auto& row : board) {
        for (ll val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    ll n, x, y;
    cin >> n >> x >> y;

    vector<vector<ll>> adj_list = build_adj_list(n);

    cout << "Graph:\n";
    for (ll i = 0; i < adj_list.size(); ++i) {
        cout << i << " - ";
        for (ll neighbor : adj_list[i]) {
            cout << neighbor << " ";
        }
        cout << "\n";
    }

    vector<bool> visited(n * n, false);
    vector<ll> path;

    cout << "Hamiltonian path:\n";

    if (hamiltonian_path(x * n + y, path, visited, adj_list)) 
        print_matrix(path, n);
    else 
        cout << "No way\n";

    return 0;
}
