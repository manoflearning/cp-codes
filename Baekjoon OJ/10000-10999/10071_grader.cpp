#include <bits/stdc++.h>
#include <cassert>
#include "game.h"
using namespace std;
#define sz(x) (int)(x).size()

int n;
multiset<int> edge[1515];

vector<int> uf(1515, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;

    uf[U] = V;

    for (auto& i : edge[U]) edge[V].insert(i);
    edge[U].clear();

    multiset<int> s = edge[V];
    for (auto& i : s) {
        if (find(i) == V) edge[V].erase(i);
    }
}

void initialize(int N) {
    n = N;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) edge[i].insert(j);
        }
    }
}

int condition(int u, int v) {
    int U = find(u), V = find(v);
    for (auto& i : edge[U]) {
        if (find(i) == V) return 0;
    }
    for (auto& i : edge[V]) {
        if (find(i) == U) return 0;
    }
    return 1;
}

int hasEdge(int u, int v) {
    if (find(u) == find(v)) return 0;

    edge[find(u)].erase(edge[find(u)].find(v));
    edge[find(v)].erase(edge[find(v)].find(u));

    if (condition(u, v)) {
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
        //hasEdge(u, v);
        printf("%d\n", hasEdge(u, v));
    }
    return 0;
}
