#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct UF {
    vector<ll> e, sum;
    void init(int n) {
        e.assign(n, -1);
        sum.assign(n, 0);
    }
    int find(int x) {
        if (e[x] < 0) return x;
        return find(e[x]);
    }
    void join(int u, int v, ll w) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (e[u] > e[v]) swap(u, v);
        sum[u] += -e[v] * w;
        sum[v] -= sum[u];
        sum[v] += -e[u] * w;
        e[u] += e[v], e[v] = u;
    }
    ll value(int x) {
        ll ret = sum[x];
        if (e[x] < 0) return ret;
        return ret + value(e[x]);
    }
};

struct Edge {
    int u, v; ll w;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<ll> d(n);
    for (auto &i : d) cin >> i;
    
    vector<Edge> e(m);
    for (auto &i : e) {
        cin >> i.u >> i.v;
        i.u--, i.v--;
        i.w = max(d[i.u], d[i.v]);
    }

    sort(all(e), [&](const Edge &i, const Edge &j) {
        return i.w < j.w;
    });

    UF uf;
    uf.init(n);
    for (const auto &i : e) {
        uf.join(i.u, i.v, i.w);
    }
    for (int i = 0; i < n; i++) {
        cout << uf.value(i) + d[i] << ' ';
    }
}
