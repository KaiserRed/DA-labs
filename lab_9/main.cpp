#include <iostream>
#include "graph.cpp"



int main() {
    int n, m, start, finish;
    std::cin >> n >> m >> start >> finish;

    std::vector<std::vector<std::pair<int, long long>>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    std::vector<long long> distance(n + 1, INF);

    dijkstra(n, start, graph, distance);

    if (distance[finish] == INF) {
        std::cout << "No solution" << std::endl;
    } else {
        std::cout << distance[finish] << std::endl;
    }

    return 0;
}