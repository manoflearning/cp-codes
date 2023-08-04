#include <bits/stdc++.h>
#include "game.h"
using namespace std;
#define sz(x) (int)(x).size()

int n;
map<int, int> edge[1515];

vector<int> uf(1515, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;

    uf[U] = V;

    for (auto& i : edge[U]) edge[V][i.first] += i.second;
    edge[U].clear();

    map<int, int> mp = edge[V];
    for (auto& i : mp) {
        if (find(i.first) == V) edge[V].erase(i.first);
    }
}

void initialize(int N) {
    n = N;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) edge[i][j]++;
        }
    }
}

int condition(int u, int v) {
    int U = find(u), V = find(v);
    for (auto& i : edge[U]) {
        if (find(i.first) == V) return 0;
    }
    for (auto& i : edge[V]) {
        if (find(i.first) == U) return 0;
    }
    return 1;
}

int hasEdge(int u, int v) {
    if (find(u) == find(v)) return 0;

    edge[find(u)][v]--;
    if (!edge[find(u)][v]) edge[find(u)].erase(v);
    edge[find(v)][u]--;
    if (!edge[find(v)][u]) edge[find(v)].erase(u);

    if (condition(u, v)) {
        merge(u, v);
        return 1;
    }
    return 0;
}
