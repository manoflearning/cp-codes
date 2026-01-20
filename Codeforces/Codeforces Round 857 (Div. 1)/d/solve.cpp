#pragma GCC optimize ("Ofast, unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 1e18;

struct State {
    ll cnt, cash;
    bool operator<(const State &rhs) const {
        return cnt ^ rhs.cnt ? cnt > rhs.cnt : cash < rhs.cash;
    }
    bool operator!=(const State &rhs) const {
        return pair<ll, ll>{cnt, cash} != pair<ll, ll>{rhs.cnt, rhs.cash};
    }
};
struct Edge {
    ll w; int v;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        ll p;
        cin >> n >> m >> p;

        vector<ll> w(n);
        for (auto &i : w) cin >> i;

        vector<vector<Edge>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; ll w;
            cin >> u >> v >> w;
            u--, v--;
            adj[u].push_back({w, v});
        }

        vector<vector<State>> dist(n, vector<State>(n, {INF, INF}));
        priority_queue<tuple<State, int, int>> pq;

        dist[0][0] = {0, p};
        pq.push({dist[0][0], 0, 0});
        
        while (!pq.empty()) {
            const auto [state, now, opt] = pq.top();
            pq.pop();

            if (state != dist[now][opt]) continue;

            if (now == n - 1) break;

            for (auto e : adj[now]) {
                const int nxt = e.v;
                const int n_opt = (w[e.v] > w[opt] ? e.v : opt);

                State n_state = state;
                if (e.w > n_state.cash) {
                    ll add = (e.w - n_state.cash + w[opt] - 1) / w[opt];
                    n_state.cnt += add;
                    n_state.cash += add * w[opt];
                }
                n_state.cash -= e.w;

                if (dist[nxt][n_opt] < n_state) {
                    dist[nxt][n_opt] = n_state;
                    pq.push({n_state, nxt, n_opt});
                }
            }
        }

        ll ans = INF;
        for (int opt = 0; opt < n; opt++)
            ans = min(ans, dist[n - 1][opt].cnt);
        cout << (ans == INF ? -1 : ans) << '\n';
    }
}
