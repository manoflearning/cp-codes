#include <bits/stdc++.h>
#include "game.h"
using namespace std;

vector<int> uf(1515, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] = V;
}

int n, deg[1515];
int qCnt = 0;

void initialize(int N) {
    n = N;
}

int hasEdge(int u, int v) {
    qCnt++;
    if (qCnt == n * (n - 1) / 2) {
        assert(find(u) != find(v));
    }

    // solve
    deg[u]++, deg[v]++;
    if (deg[u] == n - 1 || deg[v] == n - 1) return 1;
    return 0;
}
