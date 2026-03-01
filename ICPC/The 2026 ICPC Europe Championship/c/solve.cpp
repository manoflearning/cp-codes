#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

constexpr ll INF = 4e18;

ll dijkstra(ll n) {
    unordered_map<ll, ll> dist;
    priority_queue<pll, vector<pll>, greater<>> pq;

    dist[n] = 0;
    pq.push({dist[n], n});

    while (!pq.empty()) {
        const auto [w, now] = pq.top();
        pq.pop();

        if (dist[now] < w) continue;
        if (now == 1) break;

        for (ll d = 2; d <= 30; d++) {
            const ll nxt = now / d;
            if (nxt == 0) continue;
            const ll nw = w + 2 + d + now % d;
            if (dist.count(nxt) && dist[nxt] <= nw) continue;
            dist[nxt] = nw;
            pq.push({dist[nxt], nxt});
        }
    }

    ll ret = INF;
    for (const auto [k, v] : dist) {
        ret = min(ret, k + v);
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll n; cin >> n;
    cout << dijkstra(n) << '\n';
}
