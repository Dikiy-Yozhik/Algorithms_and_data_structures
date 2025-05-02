#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

vector<vector<ll>> result;
vector<ll> current;
vector<ll> indegree;
vector<bool> visited;

void topological_sort(vector<vector<ll>>& graph) {
    bool flag = false;

    for (ll i = 0; i < graph.size(); ++i) {
        if (indegree[i] == 0 && !visited[i]) {
            for (ll child : graph[i]) {
                indegree[child]--;
            }

            current.push_back(i);
            visited[i] = true;
            
            topological_sort(graph);
            
            visited[i] = false;
            current.pop_back();
            for (ll neighbor : graph[i]) {
                indegree[neighbor]++;
            }

            flag = true;
        }
    }

    if (!flag && current.size() == graph.size()) {
        result.push_back(current);
    }
}

int main() {
    ll v;
    cin >> v;
    
    vector<vector<ll>> graph(v);
    indegree.resize(v, 0);
    visited.resize(v, false);
    
    for (ll i = 0; i < v; ++i) {
        ll k;
        cin >> k;
        graph[i].resize(k);
        for (ll j = 0; j < k; ++j) {
            cin >> graph[i][j];
            indegree[graph[i][j]]++;
        }
    }
    
    topological_sort(graph);
    
    if (result.empty()) {
        cout << "Impossible\n";
    } 
    else {
        sort(result.begin(), result.end());
        
        cout << result.size() << "\n";
        for (const auto& sort_order : result) {
            for (ll i : sort_order) {
                cout << i << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
