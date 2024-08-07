// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const ll INF = 1e18;

int n, m;
struct Edge { ll w; int v; };
vector<vector<Edge>> adj;
vector<ll> siz;
ll ans = 0;

void init() {
    adj.clear();
    siz.clear();
    ans = 0;
}

void input() {
    cin >> n >> m;
    adj.resize(n + 1);
    siz.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs(int v, int prv) {
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dfs(i.v, v);
        siz[v] += siz[i.v];
        ans += i.w * siz[i.v] * (n - siz[i.v]);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        if (m == n - 1) dfs(1, 0);

        cout << ans << '\n';

        cout << flush;
    }
}