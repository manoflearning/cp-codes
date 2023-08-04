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
    uf[V] += uf[U];
    uf[U] = V;
}

int n;
set<int> s[1515];

void initialize(int N) {
    n = N;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s[i].insert(j);
        }
    }
}

int condition(int v) {
    for (int i = 0; i < n; i++) {
        if (find(i) != find(v)) continue;
        for (auto& u : s[i]) {
            if (find(v) != find(u)) return 0;
        }
    }
    
    return 1;
}

int hasEdge(int u, int v) {
    s[u].erase(v);
    s[v].erase(u);

    if (find(u) != find(v) && (condition(u) || condition(v))) {
        merge(u, v);
        return 1;
    }
    return 0;
}