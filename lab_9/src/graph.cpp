#include <iostream>
#include <vector>
#include <set>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();

//разряженный граф
void dijkstra(int n, int start, std::vector<std::vector<std::pair<int, long long>>>& graph, std::vector<long long>& distance) {
    distance[start] = 0;
    std::set<std::pair<long long, int>> s;
    s.insert({0, start});

    while (!s.empty()) {
        long long w = s.begin()->first;
        int u = s.begin()->second;
        s.erase(s.begin());

        for (auto& edge: graph[u]) {
            int v = edge.first;
            long long w1 = edge.second;
            
            if (w1 + distance[u] < distance[v]) {

                if (distance[v] != INF) {
                    s.erase({distance[v], v});
                }

                distance[v] = w1 + distance[u];
                s.insert({distance[v], v});
            }
        }
    }
}
