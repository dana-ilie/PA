#include <bits/stdc++.h>

int find_value(int x, int y, int n) {
    if (n == 1) {
        return 0;
    }

    int mid = n >> 1;
    if (x <= mid && y <= mid) {
        // top left
        return find_value(x, y, mid);
    } else if (x <= mid && y > mid) {
        // top right
        return find_value(x, y - mid, mid);
    } else if (x > mid && y <= mid) {
        // bottom left
        return find_value(x - mid, y, mid);
    } else {
        // bottom right
        return !find_value(x - mid, y - mid, mid);
    }
}

int main() {
    std::ifstream fin("walsh.in");
    std::ofstream fout("walsh.out");

    int n, k;
    fin >> n >> k;

    for (int i = 0; i < k; i++) {
        int x, y;
        fin >> x >> y;
        fout << find_value(x, y, n) << std::endl;
    }

    fin.close();
    fout.close();

    return 0;
}
