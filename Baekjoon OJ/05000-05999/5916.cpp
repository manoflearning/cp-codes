#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXV = 101010;

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void modify(int l, int r, int value, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] += value;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, value, n << 1, nl, mid);
        modify(l, r, value, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
    void propagate(int n, int nl, int nr) {
        if (lazy[n] != 0) {
            if (n < flag) {
                lazy[n << 1] += lazy[n];
                lazy[n << 1 | 1] += lazy[n];
            }
            t[n] += lazy[n] * (nr - nl + 1);
            lazy[n] = 0;
        }
    }
}seg;

int n, m;
vector<int> adj[MAXV], g[MAXV];
int siz[MAXV], dep[MAXV], par[MAXV];
int top[MAXV], in[MAXV], out[MAXV], pv;

void input() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}
void dfs(int v, int prv) {
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        g[v].push_back(i);
        dfs(i, v);
    }
}
int dfs1(int v) {
    siz[v] = 1;
    for (auto& i : g[v]) {
        dep[i] = dep[v] + 1, par[i] = v;
        siz[i] += dfs1(i);
        if (siz[i] > siz[g[v][0]]) swap(i, g[v][0]);
    }
    return siz[v];
}
void dfs2(int v) {
    in[v] = ++pv;
    for (auto& i : g[v]) {
        top[i] = (i == g[v][0] ? top[v] : i);
        dfs2(i);
    }
    out[v] = pv;
}
void modify(int u, int v) {
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        seg.modify(in[st], in[u], 1);
        u = par[st];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.modify(in[u] + 1, in[v], 1);
}
ll query(int u, int v) {
    ll ret = 0;
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        ret += seg.query(in[st], in[u]);
        u = par[st];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ret += seg.query(in[u] + 1, in[v]);
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    seg.build(n);

    dfs(1, 0);
    top[1] = 1;
    dfs1(1);
    dfs2(1);

    for (int i = 0; i < m; i++) {
        char op; int u, v;
        cin >> op >> u >> v;
        if (op == 'P') modify(u, v);
        if (op == 'Q') cout << query(u, v) << '\n';
    }
}