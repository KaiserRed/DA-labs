#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

struct Edge {
    double distance;
    int vertex;

    Edge(double dist, int v) : distance(dist), vertex(v) {}
};

struct Node {
    double f_cost;
    int vertex;

    Node(double f, int v) : f_cost(f), vertex(v) {}

    bool operator>(const Node& other) const {
        return f_cost > other.f_cost;
    }
};

inline double euclidean_distance(pair<int, int>& p1, pair<int, int>& p2) {
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

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

        if (start == goal) {
            cout << fixed << setprecision(6) << 0.0 << '\n';
            continue;
        }

        priority_queue<Node, vector<Node>, greater<Node>> pq;
        vector<double> g_cost(n + 1, numeric_limits<double>::infinity());
        vector<bool> visited(n + 1, false);

        g_cost[start] = 0;
        pq.emplace(0.0, start);

        bool path_found = false;
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            int u = current.vertex;

            if (visited[u]) continue;
            visited[u] = true;

            if (u == goal) {
                cout << fixed << setprecision(6) << g_cost[u] << '\n';
                path_found = true;
                break;
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

        if (!path_found) {
            cout << -1 << '\n';
        }
    }

    return 0;
}
