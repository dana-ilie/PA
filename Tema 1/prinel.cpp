#include <bits/stdc++.h>

int knapsack(int n, int W, std::vector<int>& w, std::vector<int>& p) {
    std::vector<std::vector<int>> dp(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i].resize(W + 1);
    }

    // base case
    for (int cap = 0; cap <= W; cap++) {
        dp[0][cap] = 0;
    }

    // general case
    for (int i = 1; i <= n; i++) {
        for (int cap = 0; cap <= W; cap++) {
           dp[i][cap] = dp[i - 1][cap];

           if (cap - w[i] >= 0) {
               int aux = dp[i - 1][cap - w[i]] + p[i];
               dp[i][cap] = std::max(dp[i][cap], aux);
           }
        }
    }

    return dp[n][W];
}

int count_operations(int n, std::vector<std::pair<int, bool>>& v) {
    if (n == 1) {
        return 0;
    }

    if (v[n].second) {
        return v[n].first;
    }

    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int, int>(1, 0));
    v[1].first = 0;
    v[1].second = true;

    while (!q.empty()) {
        int aux = q.front().first;
        int op = q.front().second;
        q.pop();

        for (int i = 1; i * i <= aux; i++) {
            if (aux % i == 0) {
                if (aux + i <= n && !v[aux + i].second) {
                    q.push(std::make_pair(aux + i, op + 1));
                    v[aux + i].first = op + 1;
                    v[aux + i].second = true;
                }

                if (aux + aux / i <= n && !v[aux + aux / i].second) {
                    q.push(std::make_pair(aux + aux / i, op + 1));
                    v[aux + aux / i].first = op + 1;
                    v[aux + aux / i].second = true;
                }
            }
        }
    }

    return -1;
}

int main() {
    std::ifstream fin("prinel.in");
    std::ofstream fout("prinel.out");

    int n, k;
    fin >> n >> k;

    std::vector<int> a(n + 1);
    std::vector<int> target(n + 1);
    std::vector<int> points(n + 1);  // value in knapsack
    std::vector<int> no_operations(n + 1);  // weight in knapsack

    int max_target = -1;
    for (int i = 1; i <= n; i++) {
        a[i] = 1;
        fin >> target[i];
        if (target[i] > max_target) {
            max_target = target[i];
        }
    }

    int total_points = 0;
    for (int i = 1; i <= n; i++) {
        fin >> points[i];
        total_points += points[i];
    }


    // (nof_operations, visited) pairs
    std::vector<std::pair<int, bool>> v(max_target + 1);
    count_operations(max_target, v);

    int total_operations = 0;
    for (int i = 1; i <=n ; i++) {
        no_operations[i] = count_operations(target[i], v);
        total_operations += no_operations[i];
    }

    if (total_operations <= k) {
        fout << total_points << std::endl;
        return 0;
    }

    int max_points = knapsack(n, k, no_operations, points);
    fout << max_points << std::endl;

    fin.close();
    fout.close();

    return 0;
}
