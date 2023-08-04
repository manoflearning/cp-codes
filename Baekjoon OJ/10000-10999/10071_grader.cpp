#include <bits/stdc++.h>
#include <cassert>
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
    for (auto& u : s[v]) {
        if (find(v) != find(u)) return 0;
    }
    return 1;
}

int hasEdge(int u, int v) {
    s[u].erase(v);
    s[v].erase(u);

    if (find(u) == find(v)) return 0;

    if (condition(u) || condition(v)) {
        merge(u, v);
        return 1;
    }
    return 0;
}

int read_int() {
    int x;
    assert(scanf("%d", &x) == 1);
    return x;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif
    
    int n, u, v;
    n = read_int();
    initialize(n);
    for (int i = 0; i < n * (n - 1) / 2; i++) {
        u = read_int();
        v = read_int();
        printf("%d\n", hasEdge(u, v));
    }
    return 0;
}
