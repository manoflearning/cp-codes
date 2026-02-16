#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int D = 62;

bool dfs(int now, int c, vector<int> &co, const vector<vector<int>> &g) {
    co[now] = c;
    for (int nxt : g[now]) {
        if (co[nxt] == -1) {
            dfs(nxt, !c, co, g);
        } else {
            if (co[nxt] == co[now]) return 0;
        }
    }
    return 1;
}

ll modpow(ll b, ll e, const ll mod) {
    if (!e) return 1;
    const ll res = modpow(b, e / 2, mod);
    return res * res % mod * (e & 1 ? b : 1) % mod;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m, p;
    cin >> n >> m >> p;

    const int mod = p;

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll ans = 1;

    vector<int> co(n, -1);
    for (int now = 0; now < n; now++) {
        if (co[now] == -1) {
            if (dfs(now, 0, co, g)) {
                ans = ans * 2 % mod;
            } else {
                cout << "impossible\n";
                exit(0);
            }
        }
    }
    ans = ans * modpow(2, mod - 2, mod) % mod;
    ans = (ans + 1) % mod;

    cout << ans << '\n';
}