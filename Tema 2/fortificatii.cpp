#include <bits/stdc++.h>

#define LONG_LONG_MAX 1000000000000000000LL

long long int min_dist(std::vector<long long int> dist, bool visited[],
                       long long int N) {
    long long int min = LONG_LONG_MAX, min_index;
    for (long long int v = 1; v <= N; v++) {
        if (visited[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}


// Refference : lab 9 public solution
void dijkstra(std::vector<std::pair<long long int,
              long long int>> adj[100005], long long int src,
              std::vector<long long int> &dist) {
    std::set<std::pair<long long int, long long int>> pq;

    dist[src] = 0;
    pq.insert(std::make_pair(0, src));

    while (!pq.empty()) {
        auto top = pq.begin();
        const auto[_, node] = *top;
        pq.erase(top);

        for (auto it = adj[node].begin(); it != adj[node].end(); it++) {
            long long int neigh = it->first;
            long long int weight = it->second;
            if (dist[node] + weight < dist[neigh]) {
                pq.erase(std::make_pair(dist[neigh], neigh));
                dist[neigh] = dist[node] + weight;
                pq.insert(std::make_pair(dist[neigh], neigh));
            }
        }
    }
}

int main() {
    std::ifstream fin("fortificatii.in");
    std::ofstream fout("fortificatii.out");

    long long int n;  // n = number of nodes(villages)
    long long int m;  // m = number of routes(roads)
    long long int k;  // k = number of fortifications to be placed
    long long int b;  // b = number of villages controlled by barbarians

    fin >> n >> m >> k >> b;

    std::vector<long long int> is_controlled(n + 1, 0);
    for (long long int i = 1; i <= b; i++) {
        long long int v;
        fin >> v;
        is_controlled[v] = 1;
    }

    // adj[node] = adjacency list of node
    // pair (neigh, cost) = edge between node and neigh with cost
    std::vector<std::pair<long long int, long long int>> adj[n + 1];

    for (long long int i = 0; i < m; i++) {
        long long int n1, n2, cost;
        fin >> n1 >> n2 >> cost;
        // if n1 is controlled by barbarians
        if (is_controlled[n1]) {
            adj[n2].push_back(std::make_pair(n1, cost));
        }

        // if n2 is controlled by barbarians
        if (is_controlled[n2]) {
            adj[n1].push_back(std::make_pair(n2, cost));
        }

        // if n1 and n2 are not controlled by barbarians
        if (!is_controlled[n1] && !is_controlled[n2]) {
            adj[n1].push_back(std::make_pair(n2, cost));
            adj[n2].push_back(std::make_pair(n1, cost));
        }
    }

    std::vector<long long int> dist(n + 1, LONG_LONG_MAX);
    dijkstra(adj, 1, dist);

    std::vector<long long int> barbarian_dist;

    long long int p = 1;
    barbarian_dist.push_back(-1);
    for (long long int i = 1; i <= n; i++) {
        for (auto j = adj[i].begin(); j != adj[i].end(); j++) {
            if (is_controlled[i] == 0 && is_controlled[j->first] == 1) {
                if (dist[i] != LONG_LONG_MAX) {
                    p++;
                    barbarian_dist.push_back(dist[i] + j->second);
                }
            }
        }
    }

    std::sort(barbarian_dist.begin(), barbarian_dist.end());

    long long int diff = -1, eq;
    long long int i;

        eq = 0;
        for (i = 1; i < p; i++) {
            if (barbarian_dist[i] == barbarian_dist[1]) {
                eq++;
            } else {
                break;
            }
        }

        if (eq == p - 1) {
            diff = 0;
        } else {
            diff = barbarian_dist[eq + 1] - barbarian_dist[1];
        }


    while (k > (eq * diff) && diff != 0) {
        k -= diff * eq;

        for (long long int i = 1; i <= eq; i++) {
            barbarian_dist[i] += diff;
        }
        eq++;

        for (i = eq + 1; i < p; i++) {
            if (barbarian_dist[i] == barbarian_dist[1]) {
                eq++;
            } else {
                break;
            }
        }

        if (eq == p - 1) {
            diff = 0;
        } else {
            diff = barbarian_dist[eq + 1] - barbarian_dist[1];
        }
    }

    fout << barbarian_dist[1] + (k / eq) << std::endl;

    fin.close();
    fout.close();

    return 0;
}
