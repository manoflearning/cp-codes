#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;

int n;
vector<vector<pll>> t;
vector<ll> siz, dp1, dp2;

void dfs1(int v, int prv) {
    siz[v] = 1;

    for (auto &[w, i] : t[v]) {
        if (i == prv) continue;
        dfs1(i, v);
        siz[v] += siz[i];
        dp1[v] += dp1[i] + siz[i] * w;
    }
}

void dfs2(int v, int prv) {
    dp2[v] = dp1[v];

    for (auto &[w, i] : t[v]) {
        if (i == prv) {
            dp2[v] += dp2[i];
            dp2[v] -= dp1[v] + siz[v] * w;
            dp2[v] += (n - siz[v]) * w;
        }
    }

    for (auto &[w, i] : t[v]) {
        if (i == prv) continue;
        dfs2(i, v);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    t.assign(n + 1, vector<pll>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        t[u].push_back({w, v});
        t[v].push_back({w, u});
    }

    siz.assign(n + 1, 0);
    dp1.assign(n + 1, 0);
    dp2.assign(n + 1, 0);

    dfs1(1, 0);
    dfs2(1, 0);

    ll ans1 = INF, ans2 = -INF;
    for (int i = 1; i <= n; i++) {
        ans1 = min(ans1, dp2[i]);
        ans2 = max(ans2, dp2[i]);
    }
    cout << ans1 << ' ' << ans2 << '\n';
}
