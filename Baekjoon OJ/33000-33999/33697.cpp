#pragma GCC optimize("O3")
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

int n, m, q;
vector<vector<int>> t1, t2;

vector<pii> dp1, dp2; // fr: 명령의 순서, sc: 색깔

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> q;
    t1.assign(n + 1, vector<int>());
    t2.assign(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        t1[u].push_back(v);
        t2[v].push_back(u);
    }

    dp1.assign(n + 1, {0, 0});
    dp2.assign(n + 1, {0, 0});

    for (int i = 1; i <= q; i++) {
        int x, d, c;
        cin >> x >> d >> c;
        if (d == 1) dp1[x] = {i, c};
        else dp2[x] = {i, c};
    }

    for (int v = 1; v <= n; v++) {
        for (int u : t1[v]) {
            if (dp1[u] < dp1[v]) dp1[u] = dp1[v];
        }
    }
    for (int v = n; v >= 1; v--) {
        for (int u : t2[v]) {
            if (dp2[u] < dp2[v]) dp2[u] = dp2[v];
        }
    }

    for (int v = 1; v <= n; v++) {
        pii res = max(dp1[v], dp2[v]);
        cout << res.sc << ' ';
    }
}
