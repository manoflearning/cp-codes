#pragma GCC optimize ("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct UF {
    vector<int> e;
    UF(int n) { e.assign(n, -1); }
    int find(int x) {
        if (e[x] < 0) return x;
        return e[x] = find(e[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        e[v] += e[u];
        e[u] = v;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m, q; cin >> n >> m >> q;

    vector<vi> g(n); UF uf(n);
    for(int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);

        uf.merge(u, v);
    }

    vi pts;

    for(int i = 0; i < n; i++) {
        if(-uf.e[uf.find(i)] > 20000) pts.push_back(i);
    }

    shuffle(all(pts), mt19937(1557));

    vector<unordered_map<int, int>> con;
    vector<vi> nx(n);

    for(int i = 0; i < min(100, sz(pts)); i++) {
        queue<int> q; q.push(pts[i]);
        vi vis(n); vis[pts[i]] = 1;
        vector<pii> res;

        for(int len = 0; len <= 20000; len++) {
            for(int j = sz(q); j > 0; j--) {
                auto u = q.front(); q.pop();
                res.push_back({u, len});

                for(auto &v:g[u]) {
                    if(vis[v]) continue;
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }

        // sort(all(res));
        for(auto &[l,r]:res) {
            nx[l].push_back(sz(con));
        }

        con.push_back({});
        for (auto &[l, r] : res) con.back()[l] = r;
    }

    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        x--, y--;

        if(uf.find(x) != uf.find(y)) {
            cout << "YES\n";
            continue;
        }

        bool isin = (sz(nx[x]) == 0);

        for(auto &xx:nx[x]) {
            if(con[xx].count(x) == 0 || con[xx].count(y) == 0) continue;
            if(con[xx][x] + con[xx][y] > 20000) continue;

            isin = 1;
            break;
        }

        if(isin) cout << "NO\n";
        else cout << "YES\n";
    }
}