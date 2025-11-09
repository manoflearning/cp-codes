#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int N = 202020;

struct node {
    array<ll, 8> v;
    node operator+(const node &rhs) const {
        array<ll, 8> ret{};
        for (int i = 0; i < 8; i++) {
            ret[i] = v[i] + rhs.v[i];
        }
        return node{ret};
    }
    bool operator!=(const node &rhs) const {
        return v != rhs.v;
    }
};

node max(const node &lhs, const node &rhs) {
    array<ll, 8> ret{};
    for (int i = 0; i < 8; i++) {
        ret[i] = max(lhs.v[i], rhs.v[i]);
    }
    return node{ret};
}

const node &E = node{array<ll, 8>{-INF, -INF, -INF, -INF, -INF, -INF, -INF, -INF}};

int flag;
struct Seg {
    vector<node> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, node{array<ll, 8>{}});
        lazy.resize(flag << 1, node{array<ll, 8>{}});
    }
    void propagate(int n) {
        if (lazy[n] != node{}) {
            if (n < flag) {
                lazy[n << 1] = lazy[n << 1] + lazy[n];
                lazy[n << 1 | 1] = lazy[n << 1 | 1] + lazy[n];
            }
            t[n] = t[n] + lazy[n];
            lazy[n] = node{array<ll, 8>{}};
        }
    }
    void add(int l, int r, const array<ll, 8> &val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);

        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] = lazy[n] + node{val};
            propagate(n);
            return;
        }

        int mid = (nl + nr) >> 1;
        add(l, r, val, n << 1, nl, mid);
        add(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = max(t[n << 1], t[n << 1 | 1]);
    }
    node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return E;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg;

int n;
struct edge { ll w; int v; };
struct point { ll x, y, z; };
vector<edge> adj[N];
point p[N];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y >> p[i].z;
    }
}

int in[N], out[N], idx;

void dfs0(int v, int prv, ll acc_w) {
    in[v] = ++idx;

    array<ll, 8> dist{};
    for (int bit = 0; bit < 8; bit++) {
        ll d = 0;
        d += (bit & (1 << 0) ? 1 : -1) * p[v].x;
        d += (bit & (1 << 1) ? 1 : -1) * p[v].y;
        d += (bit & (1 << 2) ? 1 : -1) * p[v].z;
        dist[bit] = d;
        dist[bit] = acc_w + d;
    }
    seg.add(in[v], in[v], dist);

    for (auto &i : adj[v]) {
        if (i.v == prv) continue;
        dfs0(i.v, v, acc_w + i.w);
    }

    out[v] = idx;
}

ll ans = -INF;
void dfs1(int v, int prv) {
    const auto &dist = seg.query(1, n);
    for (int bit = 0; bit < 8; bit++) {
        ll res = 0;
        res += (bit & (1 << 0) ? 1 : -1) * p[v].x;
        res += (bit & (1 << 1) ? 1 : -1) * p[v].y;
        res += (bit & (1 << 2) ? 1 : -1) * p[v].z;
        res += dist.v[7 - bit];
        ans = max(ans, res);
    }

    for (auto &i : adj[v]) {
        if (i.v == prv) continue;

        const auto pos1 = array<ll, 8>{i.w, i.w, i.w, i.w, i.w, i.w, i.w, i.w};
        const auto pos2 = array<ll, 8>{2 * i.w, 2 * i.w, 2 * i.w, 2 * i.w, 2 * i.w, 2 * i.w, 2 * i.w, 2 * i.w};
        const auto neg1 = array<ll, 8>{-i.w, -i.w, -i.w, -i.w, -i.w, -i.w, -i.w, -i.w};
        const auto neg2 = array<ll, 8>{-2 * i.w, -2 * i.w, -2 * i.w, -2 * i.w, -2 * i.w, -2 * i.w, -2 * i.w, -2 * i.w};
        
        seg.add(in[i.v], out[i.v], neg2);
        seg.add(1, n, pos1);

        dfs1(i.v, v);

        seg.add(in[i.v], out[i.v], pos2);
        seg.add(1, n, neg1);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    seg.build(n);

    dfs0(1, -1, 0);
    dfs1(1, -1);

    cout << ans;
}