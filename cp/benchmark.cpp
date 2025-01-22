#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;

struct Edge {
    double distance;
    int vertex;

    Edge(double dist, int v) : distance(dist), vertex(v) {}
};

struct Node {
    double cost;
    int vertex;

    Node(double c, int v) : cost(c), vertex(v) {}

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

inline double euclidean_distance(const pair<int, int>& p1, const pair<int, int>& p2) {
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}


double dijkstra(int start, int goal, const vector<vector<Edge>>& graph, const vector<pair<int, int>>& coordinates) {
    int n = graph.size() - 1;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<double> dist(n + 1, numeric_limits<double>::infinity());
    vector<bool> visited(n + 1, false);

    dist[start] = 0;
    pq.emplace(0.0, start);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;

        if (u == goal) {
            return dist[u];
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.vertex;
            double tentative_dist = dist[u] + edge.distance;

            if (!visited[v] && tentative_dist < dist[v]) {
                dist[v] = tentative_dist;
                pq.emplace(tentative_dist, v);
            }
        }
    }
    return -1;
}

double a_star(int start, int goal, const vector<vector<Edge>>& graph, const vector<pair<int, int>>& coordinates) {
    int n = graph.size() - 1;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<double> g_cost(n + 1, numeric_limits<double>::infinity());
    vector<bool> visited(n + 1, false);

    g_cost[start] = 0;
    pq.emplace(0.0, start);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;

        if (u == goal) {
            return g_cost[u];
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.vertex;
            double tentative_g = g_cost[u] + edge.distance;

            if (!visited[v] && tentative_g < g_cost[v]) {
                g_cost[v] = tentative_g;
                double h_cost = euclidean_distance(coordinates[v], coordinates[goal]);
                pq.emplace(g_cost[v] + h_cost, v);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    cout << "n = " << n << " m = " << m << " \n";

    vector<pair<int, int>> coordinates(n + 1);
    vector<vector<Edge>> graph(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> coordinates[i].first >> coordinates[i].second;
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        double dist = euclidean_distance(coordinates[u], coordinates[v]);
        graph[u].emplace_back(dist, v);
        graph[v].emplace_back(dist, u);
    }

    int q;
    cin >> q;

    while (q--) {
        int start, goal;
        cin >> start >> goal;

        auto start_time = chrono::high_resolution_clock::now();
        double dijkstra_result = dijkstra(start, goal, graph, coordinates);
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> dijkstra_duration = end_time - start_time;

        start_time = chrono::high_resolution_clock::now();
        double a_star_result = a_star(start, goal, graph, coordinates);
        end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> a_star_duration = end_time - start_time;

        cout << fixed << setprecision(6);
        cout << "Dijkstra time: " << dijkstra_duration.count() << " s\n";
        cout << "A* time: " << a_star_duration.count() << " s\n";
        cout << "Dijkstra result: " << dijkstra_result << '\n';
        cout << "A* result: " << a_star_result << '\n';
    }

    return 0;
}
