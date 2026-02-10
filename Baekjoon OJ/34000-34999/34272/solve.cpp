#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

bool dfs1(int now, int prv, vector<int> &par, vector<ll> &sum, vector<int> &ord, const ll k, const vector<ll> &w, const vector<vector<int>> &adj) {
    bool ret = 1;

    par[now] = prv;

    sum[now] = (w[now] != -1 ? w[now] : 0);
    for (const int nxt : adj[now]) {
        if (nxt == prv) continue;

        ret &= dfs1(nxt, now, par, sum, ord, k, w, adj);
        if (w[nxt] != -1) sum[now] += w[nxt];
    }

    ord.push_back(now);

    ret &= sum[now] <= k;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n;
    ll k;
    cin >> n >> k;

    vector<ll> w(n);
    for (auto &i : w) cin >> i;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> par(n), ord;
    vector<ll> sum(n);
    if (!dfs1(0, -1, par, sum, ord, k, w, adj)) {
        cout << -1 << '\n';
        return 0;
    }

    ll ans = 0;
    for (const int v : ord) {
        if (w[v] != -1) {
            ans += w[v];
        } else {
            const ll both = min(k - sum[v], k - (par[v] >= 0 ? sum[par[v]] : 0));
            sum[v] += both;
            if (par[v] >= 0) sum[par[v]] += both;
            ans += both;
        }
    }

    cout << ans << '\n';
}
