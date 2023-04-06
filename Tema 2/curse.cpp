#include <bits/stdc++.h>
// Toposort refference: lab 7 public solution
void dfs(int node, std::vector<int> &used, std::vector<int> &toposort,
         std::vector<int> adj[100005]) {
    used[node] = 1;

    // iterate through all the neighbours
    for (auto& neigh : adj[node]) {
        if (!used[neigh])
            dfs(neigh, used, toposort, adj);
    }

    toposort.push_back(node);
}

int main() {
    std::ifstream fin("curse.in");
    std::ofstream fout("curse.out");

    int n;  // n = number of tracks
    int m;  // m = number of cars
    int a;  // a = number of trainings
    fin >> n >> m >> a;

    std::vector<std::vector<int>> tracks(n + 1, std::vector<int>(a + 1));
    // adj[node] = adjacency list of node
    std::vector<int> adj[m + 1];

    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= n; j++) {
            int car;
            fin >> car;
            tracks[j][i] = car;
        }
    }

    std::vector<int> used(a - 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < a; j++) {
            if (tracks[i][j] != tracks[i][j + 1]) {
                if (used[j] == 0) {
                    adj[tracks[i][j]].push_back(tracks[i][j + 1]);
                    used[j] = 1;
                }
            }
        }
    }

    std::vector<int> toposort;
    std::vector<int> visited(m + 1, 0);

    for (int i = 1; i <= m; i++) {
        if (!visited[i]) {
            dfs(i, visited, toposort, adj);
        }
    }

    std::reverse(toposort.begin(), toposort.end());

    // print toposort
    for (auto& node : toposort) {
        fout << node << " ";
    }

    return 0;
}
