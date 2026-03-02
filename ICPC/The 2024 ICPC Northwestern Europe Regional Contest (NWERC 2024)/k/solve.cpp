#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;
constexpr ld EPS = 1e-8;

struct Edge {
    ll w; int nxt;
};

struct Store {
    int loc; ld p;
};

vector<ll> dijkstra(int st, const int n, const vector<vector<Edge>> &g) {
    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[st] = 0;
    pq.push({dist[st], st});

    while (!pq.empty()) {
        const auto [w, now] = pq.top();
        pq.pop();

        if (dist[now] < w) continue;

        for (const auto &e : g[now]) {
            if (dist[e.nxt] <= w + e.w) continue;
            dist[e.nxt] = w + e.w;
            pq.push({dist[e.nxt], e.nxt});
        }
    }

    return dist;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(15);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<Edge>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        u--, v--;
        g[u].push_back({l, v});
        g[v].push_back({l, u});
    }

    bool yes = 0;

    vector<Store> a;
    for (int i = 0; i < k; i++) {
        int v; string p;
        cin >> v >> p, v--;
        a.push_back(Store{v, stold(p)});
        yes |= (abs(a.back().p - 1.0l) < EPS);
    }

    if (!yes) {
        cout << "impossible\n";
        exit(0);
    }

    vector<ll> dist_st = dijkstra(0, n, g);
    vector<ll> dist_en = dijkstra(n - 1, n, g);

    sort(all(a), [&](Store i, Store j) {
        return dist_st[i.loc] + dist_en[i.loc] < dist_st[j.loc] + dist_en[j.loc];
    });

    ld ans{}, acc{1.0l};
    for (const auto &i : a) {
        ans += acc * i.p * (dist_st[i.loc] + dist_en[i.loc]);
        acc *= (1.0l - i.p);
    }

    cout << ans << '\n';
}
