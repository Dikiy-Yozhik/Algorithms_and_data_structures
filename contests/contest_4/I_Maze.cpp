#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;

vector<string> labyrinth;

vector<ll> get_neighbors(ll i, ll j, ll rows, ll cols) {
    vector<ll> neighbors;
    
    if (labyrinth[i][j] == '#') {
        return neighbors;
    }
    //up
    if (i > 0 && labyrinth[i-1][j] != '#') {
        neighbors.push_back((i-1)*cols + j);
    }
    //left
    if (j > 0 && labyrinth[i][j-1] != '#') {
        neighbors.push_back(i*cols + (j-1));
    }
    //right
    if (j < cols-1 && labyrinth[i][j+1] != '#') {
        neighbors.push_back(i*cols + (j+1));
    }
    //down
    if (i < rows-1 && labyrinth[i+1][j] != '#') {
        neighbors.push_back((i+1)*cols + j);
    }
    
    return neighbors;
}

vector<vector<ll>> build_adj_list(ll rows, ll cols) {
    vector<vector<ll>> adj_list(rows * cols);
    
    for (ll i = 0; i < rows; ++i) {
        for (ll j = 0; j < cols; ++j) {
            ll cell_number = i * cols + j;
            adj_list[cell_number] = get_neighbors(i, j, rows, cols);
        }
    }
    
    return adj_list;
}

void print_graph(const vector<vector<ll>>& adj_list) {
    for (size_t i = 0; i < adj_list.size(); ++i) {
        cout << i << " - ";
        if (adj_list[i].empty()) {
            cout << "None";
        } else {
            for (size_t j = 0; j < adj_list[i].size(); ++j) {
                if (j != 0) cout << " ";
                cout << adj_list[i][j];
            }
        }
        cout << "\n";
    }
}

vector<vector<ll>> bfs(const vector<vector<ll>>& adj, ll start, ll target, ll rows, ll cols) {
    ll V = adj.size();
    vector<ll> distance(V, -1);
    queue<ll> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        
        if (v == target) break;

        for (ll u : adj[v]) {
            if (distance[u] == -1) {
                distance[u] = distance[v] + 1;
                q.push(u);
            }
        }
    }

    vector<vector<ll>> result(rows, vector<ll>(cols, -1));
    for (ll i = 0; i < rows; ++i) {
        for (ll j = 0; j < cols; ++j) {
            ll cell = i * cols + j;
            if (labyrinth[i][j] == '#') {
                result[i][j] = -1;
            } 
            else {
                result[i][j] = distance[cell];
            }
        }
    }

    return result;
}

int main() {
    ll rows, cols;
    cin >> rows >> cols;
    
    labyrinth.resize(rows);
    for (ll i = 0; i < rows; ++i) {
        cin >> labyrinth[i];
    }
    
    cout << "Initial labyrinth:\n";
    for (const auto& row : labyrinth) {
        cout << row << "\n";
    }
    
    vector<vector<ll>> adjacency_list = build_adj_list(rows, cols);
    
    cout << "Graph:\n";
    print_graph(adjacency_list);
    
    ll start = -1, target = -1;
    for (ll i = 0; i < rows; ++i) {
        for (ll j = 0; j < cols; ++j) {
            if (labyrinth[i][j] == 'S') start = i * cols + j;
            else if (labyrinth[i][j] == 'F') target = i * cols + j;
        }
    }
    
    if (start == -1 || target == -1) {
        return 1;
    }
    
    vector<vector<ll>> result = bfs(adjacency_list, start, target, rows, cols);
    
    cout << "BFS result is:\n";
    for (const auto& row : result) {
        for (ll j = 0; j < row.size(); ++j) {
            if (j != 0) cout << " ";
            cout << row[j];
        }
        cout << "\n";
    }
    
    return 0;
}
