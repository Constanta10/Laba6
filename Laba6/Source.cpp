#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Структура для представления графа списками смежности
class Graph {
    int V; // Количество вершин
    vector<vector<int>> adj; // Списки смежности

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Добавление ребра в граф
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Функция для подсчета числа кратчайших путей длины k
    int countShortestPaths(int src, int dst, int k) {
        // Матрица для хранения числа кратчайших путей
        vector<vector<int>> dp(V, vector<int>(V, 0));

        // Инициализация матрицы для k = 0
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (i == j)
                    dp[i][j] = 1; // Путь из вершины в саму себя длины 0 равен 1
                else
                    dp[i][j] = 0;
            }
        }

        // Вычисляем число кратчайших путей для каждой вершины
        // и каждой пары вершин (i, j) длины k
        for (int l = 1; l <= k; ++l) {
            vector<vector<int>> temp(V, vector<int>(V, 0));
            for (int u = 0; u < V; ++u) {
                for (int v : adj[u]) {
                    for (int w = 0; w < V; ++w) {
                        temp[u][w] += dp[v][w];
                    }
                }
            }
            dp = temp;
        }

        return dp[src][dst];
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    int V, E;
    cout << "Введите количество вершин и ребер в графе: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Введите ребра графа (вершины должны быть от 0 до " << V - 1 << "):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cout << "Введите ребро " << i + 1 << ": ";
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int src, dst, k;
    cout << "Введите начальную и конечную вершины и длину пути: ";
    cin >> src >> dst >> k;

    int numPaths = g.countShortestPaths(src, dst, k);

    cout << "Число кратчайших путей длины " << k << " от вершины " << src << " к вершине " << dst << ": " << numPaths << endl;

    return 0;
}
