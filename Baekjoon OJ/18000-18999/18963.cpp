#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
        for (int i = flag; i < flag + N; i++) t[i] = 1;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void propagate(int n) {
        if (!lazy[n]) return;
        if (n < flag) {
            lazy[n << 1] = lazy[n];
            lazy[n << 1 | 1] = lazy[n];
        }
        t[n] = lazy[n] = 0;
    }
    void modify(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] = 1;
            propagate(n);
            return;
        }

        int mid = (nl + nr) >> 1;
        modify(l, r, n << 1, nl, mid);
        modify(l, r, n << 1 | 1, mid + 1, nr);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

// 
const int MAX = 101010;

int n, m;
vector<int> adj[MAX], g[MAX];
int siz[MAX], dep[MAX], par[MAX];
int top[MAX], in[MAX], out[MAX], pv;

struct PhoneLine {
    int a, b, c, d; ll w;
};
vector<PhoneLine> pl;

void input() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pl.resize(m);
    for (auto& i : pl)
        cin >> i.a >> i.b >> i.c >> i.d >> i.w;
}

// build HLD
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
        siz[v] += dfs1(i);
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

// operation on each chain
void modify(int u, int v) {
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        seg.modify(in[st], in[u]);
        u = par[st];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.modify(in[u], in[v]);
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
    ret += seg.query(in[u], in[v]);
    return ret;
}
int lca(int u, int v) {
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        u = par[st];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}
ll sum(int a, int b, int c, int d) {
    if (dep[a] > dep[b]) swap(a, b);
    if (dep[c] > dep[d]) swap(c, d);

    int ab = lca(a, b), cd = lca(c, d);

    ll ret = query(a, b) + query(c, d);
    if (ab == a && cd == c) {
        
    }
    else if (ab == a) {

    }
    else if (cd == c) {

    }
    else {

    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    // build HLD
    dfs(1, 0);
    top[1] = 1;
    dfs1(1);
    dfs2(1);

    // solve
    seg.build(n);

    modify(1, 1);

    // find intersection of two path.
    // 
}