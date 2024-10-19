#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 998244353;

ll powxy(ll x, ll y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  ll res = powxy(x, y / 2);
  return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int n;
vector<int> p;
vector<ll> a;
vector<bool> vis;
ll all = 0;

void init() {
    p.clear();
    a.clear();
    vis.clear();
    all = 0;
}

void input() {
    cin >> n;
    p.resize(n + 1);
    a.resize(n + 1);
    vis.resize(n + 1);
    all = 0;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        all += a[i];
    }
}

struct UF {
    vector<int> uf;
    vector<ll> cc, pp, avg;
    void build(int n) {
        uf.clear();
        cc.clear();
        pp.clear();
        avg.clear();

        uf.resize(n + 1, -1);
        cc.resize(n + 1);
        pp.resize(n + 1);
        avg.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            avg[i] = 1;
            cc[i] = 1;
            pp[i] = a[i];
        }
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        avg[U] =
            avg[U] * pp[U] % MOD * powxy((pp[U] + pp[V]) % MOD, MOD - 2) % MOD
            + (cc[U] + avg[V]) * pp[V] % MOD * powxy((pp[U] + pp[V]) % MOD, MOD - 2) % MOD;
        avg[U] %= MOD;
        cc[U] += cc[V];
        pp[U] += pp[V];
        uf[V] = U;
    }
}uf;

struct Node {
    ll cc, pp, avg;
    int v;
    bool operator<(const Node& o) const {
        return pp * o.cc < o.pp * cc;
    }
};

void solve() {
    uf.build(n);
    priority_queue<Node> pq;
    for (int v = 1; v <= n; v++) {
        pq.push({ uf.cc[v], uf.pp[v], uf.avg[v], v });
    }

    while (!pq.empty()) {
        Node now = pq.top();
        pq.pop();

        if (uf.cc[now.v] != now.cc || vis[now.v]) continue;
        vis[now.v] = 1;

        int par = uf.find(p[now.v]);
        uf.merge(par, now.v);

        if (par != 0) {
            pq.push({ uf.cc[par], uf.pp[par], uf.avg[par], par });
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        solve();

        cout << uf.avg[0] << '\n';
    }
}
