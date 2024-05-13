#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ��������� ��� ������������� ����� �������� ���������
class Graph {
    int V; // ���������� ������
    vector<vector<int>> adj; // ������ ���������

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // ���������� ����� � ����
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // ������� ��� �������� ����� ���������� ����� ����� k
    int countShortestPaths(int src, int dst, int k) {
        // ������� ��� �������� ����� ���������� �����
        vector<vector<int>> dp(V, vector<int>(V, 0));

        // ������������� ������� ��� k = 0
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (i == j)
                    dp[i][j] = 1; // ���� �� ������� � ���� ���� ����� 0 ����� 1
                else
                    dp[i][j] = 0;
            }
        }

        // ��������� ����� ���������� ����� ��� ������ �������
        // � ������ ���� ������ (i, j) ����� k
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
    cout << "������� ���������� ������ � ����� � �����: ";
    cin >> V >> E;

    Graph g(V);

    cout << "������� ����� ����� (������� ������ ���� �� 0 �� " << V - 1 << "):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cout << "������� ����� " << i + 1 << ": ";
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int src, dst, k;
    cout << "������� ��������� � �������� ������� � ����� ����: ";
    cin >> src >> dst >> k;

    int numPaths = g.countShortestPaths(src, dst, k);

    cout << "����� ���������� ����� ����� " << k << " �� ������� " << src << " � ������� " << dst << ": " << numPaths << endl;

    return 0;
}
