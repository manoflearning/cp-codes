#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

struct EdgeRaw { int u, v, c; ll w; };
struct Edge { int nxt; ll w; };

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m, k;
    cin >> n >> m >> k;

    vector<EdgeRaw> e;
    vector<pii> h;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        u--, v--;

        int l; cin >> l;
        while (l--) {
            int c; cin >> c;
            e.push_back({u, v, c, w});
            h.push_back({u, c});
        }
    }

    for (int i = 0; i < n; i++) h.push_back({i, 0});

    sort(all(h));
    h.erase(unique(all(h)), h.end());

    vector<vector<Edge>> g(sz(h));
    vector<int> ind(sz(h));
    for (const auto [u, v, c, w] : e) {
        const int now = lower_bound(all(h), pii{v, 0}) - h.begin();
        const int nxt = lower_bound(all(h), pii{u, c}) - h.begin();
        g[now].push_back({nxt, w});
        ind[nxt]++;
    }

    vector<ll> dist(sz(h));
    for (int i = 0; i < sz(h); i++) 
        if (h[i].second == 0) dist[i] = INF;

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[sz(h) - 1] = 0;
    pq.push({dist[sz(h) - 1], sz(h) - 1});

    while (!pq.empty()) {
        const auto [w, now] = pq.top();
        pq.pop();

        if (dist[now] < w) continue;

        if (h[now].second == 0) {
            for (const auto [nxt, nw] : g[now]) {
                dist[nxt] = max(dist[nxt], w + nw);
                if (--ind[nxt]) continue;
                pq.push({dist[nxt], nxt});
            }
        } else {
            const int nxt = lower_bound(all(h), pii{h[now].first, 0}) - h.begin();
            if (dist[nxt] > w) {
                dist[nxt] = w;
                pq.push({dist[nxt], nxt});
            }
        }
    }

    if (dist[0] >= INF) {
        cout << "impossible\n";
    } else {
        cout << dist[0] << '\n';
    }
}
