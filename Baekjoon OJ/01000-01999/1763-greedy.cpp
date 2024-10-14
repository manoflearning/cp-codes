#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 1010;
const ll INF = 1e18;

int n, ro, par[MAXN];
ll c[MAXN];

void input() {
    cin >> n >> ro;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        par[v] = u;
    }
}

struct UF {
    vector<int> uf;
    vector<ll> t, s, w;
    void build(int n) {
        uf.resize(n + 1, -1);
        t.resize(n + 1, 1);
        s.resize(n + 1);
        w.resize(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = w[i] = c[i];
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        s[u] += s[v];
        w[u] += t[u] * s[v] + w[v];
        t[u] += t[v];
        uf[v] = u;
    }
}uf;

struct Node {
    ll t, s, w;
    int v;
    bool operator<(const Node& rhs) const {
        return s * rhs.t < rhs.s * t;
    }
};

void solve() {
    uf.build(n);

    priority_queue<Node> pq;
    for (int v = 1; v <= n; v++) {
        if (v == ro) continue;
        pq.push({ uf.t[v], uf.s[v], uf.w[v], v });
    }
    
    while (!pq.empty()) {
        auto now = pq.top();
        pq.pop();

        now.v = uf.find(now.v);
        if (now.t != uf.t[now.v]) continue;

        int p = uf.find(par[now.v]);
        uf.merge(p, now.v);

        if (p != ro) pq.push({ uf.t[p], uf.s[p], uf.w[p], p });
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << uf.w[uf.find(ro)];
}
