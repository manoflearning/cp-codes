// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
vector<int> adj[202020];

bool vis[202020];
pll dfs(int v) {
    vis[v] = 1;

    pll ret = { 0, 0 };
    ret.fr += 1;
    ret.sc += sz(adj[v]);
    for (auto& i : adj[v]) {
        if (!vis[i]) {
            auto res = dfs(i);
            ret.fr += res.fr;
            ret.sc += res.sc;
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll ans = 0;
    for (int v = 1; v <= n; v++) {
        if (vis[v]) continue;
        auto res = dfs(v);
        res.sc /= 2;
        ans += res.fr * (res.fr - 1) / 2 - res.sc;
    }

    cout << ans;
}