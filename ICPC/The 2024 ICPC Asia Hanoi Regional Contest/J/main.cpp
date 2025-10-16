#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 505050;
const int M = 505050;
const int INF = 1e9 + 7;

struct UF {
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
        uf[V] += uf[U];
        uf[U] = V;
    }
} uf;

int n, m;
struct Edge {
    int u, v; ll w;
    bool operator<(const Edge &rhs) const {
        return w < rhs.w;
    }
};
vector<Edge> e;

void init() {
    e.clear();
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        e.push_back({u, v, w});
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        uf.build(n);

        ll ans = 0;
        ll cnt = 0;

        sort(all(e));
        for (auto &i : e) {
            if (uf.find(i.u) == uf.find(i.v)) continue;

            ans += i.w * uf.uf[uf.find(i.u)] * uf.uf[uf.find(i.v)];
            cnt += uf.uf[uf.find(i.u)] * uf.uf[uf.find(i.v)];

            uf.merge(i.u, i.v);

            // t[i.u].push_back({i.v, i.w});
            // t[i.v].push_back({i.u, i.w});
            // ec.push_back(i);
        }

        cout << ans << ' ' << cnt << '\n';

        // dfs(1, 0);

        // seg.build(n);

        // reverse(all(ec));

        // for (auto &i : ec) {
        //     int x = (dep[i.u] < dep[i.v] ? i.v : i.u);


        // }
    }
}
