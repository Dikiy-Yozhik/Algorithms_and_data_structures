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
        graph.coordinates.push_back(make_pair(x, y));
        graph.adjacency.push_back(vector<Edge>());
        graph.city_count++;
    }

    int id = graph.city_to_id[name];
    graph.coordinates[id] = make_pair(x, y);
}

void add_connection(Graph& graph, const string& from, const string& to) {
    int from_id = graph.city_to_id[from];
    int to_id = graph.city_to_id[to];
    
    int x1 = graph.coordinates[from_id].first;
    int y1 = graph.coordinates[from_id].second;
    int x2 = graph.coordinates[to_id].first;
    int y2 = graph.coordinates[to_id].second;
    double dist = compute_distance(x1, y1, x2, y2);
    
    bool exists = false;
    for (const Edge& e : graph.adjacency[from_id]) {
        if (e.to == to_id) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        graph.adjacency[from_id].push_back(Edge{to_id, dist});
        graph.adjacency[to_id].push_back(Edge{from_id, dist});
    }
}

Graph read_input() {
    Graph graph;
    int city_count;
    cin >> city_count;
    cin.ignore(); // Пропускаем перевод строки после числа городов

    // Читаем информацию о городах
    for (int i = 0; i < city_count; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        
        // Читаем название города и координаты
        string city_name;
        int x, y;
        iss >> city_name >> x >> y;
        
        // Добавляем город в граф (если его еще нет)
        if (graph.city_to_id.count(city_name) == 0) {
            int new_id = graph.city_count++;
            graph.city_to_id[city_name] = new_id;
            graph.id_to_city.push_back(city_name);
            graph.coordinates.push_back(make_pair(x, y));
            graph.adjacency.resize(graph.city_count);
        }
        
        // Читаем соседей и добавляем связи
        string neighbor;
        while (iss >> neighbor) {
            // Если сосед еще не добавлен в граф, добавляем его с нулевыми координатами
            // (координаты обновим при обработке его строки)
            if (graph.city_to_id.count(neighbor) == 0) {
                int new_id = graph.city_count++;
                graph.city_to_id[neighbor] = new_id;
                graph.id_to_city.push_back(neighbor);
                graph.coordinates.push_back(make_pair(0, 0));
                graph.adjacency.resize(graph.city_count);
            }
            
            // Добавляем связь между городами
            int from_id = graph.city_to_id[city_name];
            int to_id = graph.city_to_id[neighbor];
            
            // Вычисляем расстояние
            int x1 = graph.coordinates[from_id].first;
            int y1 = graph.coordinates[from_id].second;
            int x2 = graph.coordinates[to_id].first;
            int y2 = graph.coordinates[to_id].second;
            double dist = compute_distance(x1, y1, x2, y2);
            
            // Проверяем, нет ли уже такой связи
            bool exists = false;
            for (const Edge& e : graph.adjacency[from_id]) {
                if (e.to == to_id) {
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                graph.adjacency[from_id].push_back(Edge{to_id, dist});
                graph.adjacency[to_id].push_back(Edge{from_id, dist});
            }
        }
    }

    return graph;
}

pair<string, string> read_start_end(const Graph& graph) {
    string start, end;
    cin >> start >> end;
    return make_pair(start, end);
}

vector<int> dijkstra(const Graph& graph, int start_id, int end_id, vector<double>& distances) {
    const int n = graph.city_count;
    vector<int> prev(n, -1);
    distances.assign(n, numeric_limits<double>::max());
    distances[start_id] = 0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push(make_pair(0, start_id));

    while (!pq.empty()) {
        double current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == end_id) break;
        if (current_dist > distances[u]) continue;

        for (const Edge& edge : graph.adjacency[u]) {
            int v = edge.to;
            double new_dist = distances[u] + edge.distance;
            if (new_dist < distances[v]) {
                distances[v] = new_dist;
                prev[v] = u;
                pq.push(make_pair(new_dist, v));
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
    pair<string, string> start_end = read_start_end(graph);
    string start = start_end.first;
    string end = start_end.second;

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