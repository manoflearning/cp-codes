#include <bits/stdc++.h>
#include "game.h"
using namespace std;
#define sz(x) (int)(x).size()

int n;
pair<int, int> edges[1515 * 1515];
set<int> idx[1515];

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

void initialize(int N) {
    n = N;
    int p = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges[i * n + j] = { i, j };
            idx[i].insert(p);
            idx[j].insert(p);
            p++;
        }
    }
}

int hasEdge(int u, int v) {
    if (u > v) swap(u, v);
    int p = u * n + v;
    u = find(u), v = find(v);
    edges[p] = { n, n };
    idx[u].erase(p);
    idx[v].erase(p);

    if (!idx[u].find(p)) {
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
