#include <iostream>
#include <vector>
#include <climits>

using namespace std;
using ll = long long;

vector<vector<ll>> cost; 

ll choose_next_greedy(ll current, const vector<bool>& visited) {
    ll next = -1;
    ll min_cost = LLONG_MAX;
    
    for (ll j = 0; j < cost.size(); ++j) {
        if (!visited[j] && cost[current][j] > 0 && cost[current][j] < min_cost) {
            min_cost = cost[current][j];
            next = j;
        }
    }
    return next;
}

bool hamiltonian_cycle(ll start, vector<ll>& path, ll& total_cost) {
    vector<bool> visited(cost.size(), false);
    ll current = start;
    path.push_back(current);
    visited[current] = true;
    total_cost = 0;

    for (ll step = 0; step < cost.size() - 1; ++step) {
        ll next = choose_next_greedy(current, visited);
        if (next == -1) return false;
        
        total_cost += cost[current][next];
        path.push_back(next);
        visited[next] = true;
        current = next;
    }

    if (cost[current][start] == 0) return false;
    
    total_cost += cost[current][start];
    path.push_back(start);
    return true;
}

int main() {
    ll n;
    cin >> n;

    cost.resize(n, vector<ll>(n));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cin >> cost[i][j];
        }
    }

    vector<ll> best_path;
    ll min_cost = LLONG_MAX;

    for (ll start = 0; start < n; ++start) {
        vector<ll> path;
        ll current_cost;
        
        if (hamiltonian_cycle(start, path, current_cost)) {
            if (current_cost < min_cost) {
                min_cost = current_cost;
                best_path = path;
            }
        }
    }

    if (best_path.empty()) {
        cout << "Lost";
    } 
    else {
        cout << "Path:\n";
        for (size_t i = 0; i < best_path.size(); ++i) {
            cout << best_path[i];
            if (i != best_path.size() - 1) cout << " ";
        }
        cout << "\nCost: " << min_cost;
    }

    return 0;
}
