#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

struct UnionFind {
    vector<int> uf;
    void build(int n) {
        uf.clear();
        uf.resize(n + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
}uf;

int n, m, k;
struct Edge { int u, v; };
vector<Edge> er, eb;

void init() {
    er.clear();
    eb.clear();
}

void input() {
    cin >> n >> m >> k;
    if (n == 0 && m == 0 && k == 0) exit(0);
    
    for (int i = 0; i < m; i++) {
        char co; int u, v;
        cin >> co >> u >> v;
        if (co == 'R') er.push_back({ u, v });
        if (co == 'B') eb.push_back({ u, v });
    }
}

int min_blue() {
    int ret = 0;
    uf.build(n);
    for (auto& i : er) {
        uf.merge(i.u, i.v);
    }
    for (auto& i : eb) {
        if (uf.find(i.u) == uf.find(i.v)) continue;
        uf.merge(i.u, i.v);
        ret++;
    }
    return ret;
}

int max_blue() {
    int ret = 0;
    uf.build(n);
    for (auto& i : eb) {
        if (uf.find(i.u) == uf.find(i.v)) continue;
        uf.merge(i.u, i.v);
        ret++;
    }
    for (auto& i : er) {
        uf.merge(i.u, i.v);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {    
        init();

        input();

        bool ans = 1;
        ans &= (min_blue() <= k);
        ans &= (k <= max_blue());

        cout << (ans ? 1 : 0) << '\n';
    }
}
