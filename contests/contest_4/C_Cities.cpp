#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cmath>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    double distance;
};

struct Graph {
    unordered_map<string, int> city_to_id;
    vector<string> id_to_city;
    vector<pair<int, int>> coordinates;
    vector<vector<Edge>> adjacency;
    int city_count = 0;
};

double compute_distance(int x1, int y1, int x2, int y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

void add_city(Graph& graph, const string& name, int x, int y) {
    if (graph.city_to_id.find(name) == graph.city_to_id.end()) {
        graph.city_to_id[name] = graph.city_count;
        graph.id_to_city.push_back(name);
        graph.coordinates.emplace_back(x, y);
        graph.adjacency.emplace_back();
        graph.city_count++;
    }

    int id = graph.city_to_id[name];
    graph.coordinates[id] = {x, y};
}

void add_connection(Graph& graph, const string& from, const string& to) {
    int from_id = graph.city_to_id[from];
    int to_id = graph.city_to_id[to];
    
    auto [x1, y1] = graph.coordinates[from_id];
    auto [x2, y2] = graph.coordinates[to_id];
    double dist = compute_distance(x1, y1, x2, y2);
    
    bool exists = false;
    for (const Edge& e : graph.adjacency[from_id]) {
        if (e.to == to_id) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        graph.adjacency[from_id].push_back({to_id, dist});
        graph.adjacency[to_id].push_back({from_id, dist});
    }
}

Graph read_input() {
    Graph graph;
    int v;
    cin >> v;
    cin >> ws;

    vector<tuple<string, int, int, vector<string>>> city_data;
    for (int i = 0; i < v; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);

        string city_name;
        int x, y;
        iss >> city_name >> x >> y;
        
        vector<string> neighbors;
        string neighbor;
        while (iss >> neighbor) {
            neighbors.push_back(neighbor);
        }
        
        city_data.emplace_back(city_name, x, y, neighbors);
    }

    for (const auto& [name, x, y, _] : city_data) {
        add_city(graph, name, x, y);
    }

    for (const auto& [name, _, __, neighbors] : city_data) {
        for (const string& neighbor : neighbors) {
            add_connection(graph, name, neighbor);
        }
    }

    return graph;
}

pair<string, string> read_start_end(const Graph& graph) {
    string start, end;
    cin >> start >> end;
    return {start, end};
}

vector<int> dijkstra(const Graph& graph, int start_id, int end_id, vector<double>& distances) {
    const int n = graph.city_count;
    vector<int> prev(n, -1);
    distances.assign(n, numeric_limits<double>::max());
    distances[start_id] = 0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, start_id});

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (u == end_id) break;
        if (current_dist > distances[u]) continue;

        for (const Edge& edge : graph.adjacency[u]) {
            int v = edge.to;
            double new_dist = distances[u] + edge.distance;
            if (new_dist < distances[v]) {
                distances[v] = new_dist;
                prev[v] = u;
                pq.push({new_dist, v});
            }
        }
    }
    return prev;
}

vector<string> reconstruct_path(const Graph& graph, const vector<int>& prev, int end_id) {
    vector<string> path;
    if (prev[end_id] == -1) return path;

    for (int at = end_id; at != -1; at = prev[at]) {
        path.push_back(graph.id_to_city[at]);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    Graph graph = read_input();
    auto [start, end] = read_start_end(graph);

    if (graph.city_to_id.find(start) == graph.city_to_id.end() || 
        graph.city_to_id.find(end) == graph.city_to_id.end()) {
        cout << "Path:\nNo way" << endl;
        return 0;
    }

    int start_id = graph.city_to_id[start];
    int end_id = graph.city_to_id[end];

    vector<double> distances;
    vector<int> prev = dijkstra(graph, start_id, end_id, distances);
    vector<string> path = reconstruct_path(graph, prev, end_id);

    if (path.empty() || distances[end_id] == numeric_limits<double>::max()) {
        cout << "Path:\nNo way" << endl;
    } else {
        int rounded_distance = ceil(distances[end_id]);
        cout << "Path is not greater than " << rounded_distance << endl;
        cout << "Path:" << endl;
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

