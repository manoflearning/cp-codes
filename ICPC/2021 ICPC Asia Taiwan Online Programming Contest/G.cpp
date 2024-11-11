#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;
const ll INF = 1e18;

int n;
pii par[MAXN];
vector<pii> adj[MAXN], chd[MAXN];

map<ll, ll> dp1[MAXN], dp2[MAXN];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
}

void dfs(int v, int prv) {
    for (auto &[w, i] : adj[v]) {
        if (i == prv) continue;
        par[i] = {w, v};
        chd[v].push_back({w, i});
        dfs(i, v);
    }
}

ll ans = 0;

void solve(int v) {
    for (auto &[w, i] : chd[v]) {
        solve(i);

        dp1[v][w] += 1;
        dp2[v][w] += 1;
        for (auto it : dp1[i])
            if (it.fr < w) dp1[v][w] += it.sc;
        for (auto it : dp2[i])
            if (w < it.fr) dp2[v][w] += it.sc;
    }

    for (auto it : dp1[v]) ans += it.sc;
    for (auto it : dp2[v]) ans += it.sc;

    ll acc = 0;
    auto prv = dp1[v].begin();
    for (auto it : dp2[v]) {
        while (prv != dp1[v].end() && prv->fr < it.fr) {
            acc += prv->sc;
            prv++;
        }
        ans += acc * it.sc;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    input();

    for (int v = 1; v <= n; v++) sort(all(adj[v]));

    dfs(1, -1);

    solve(1);

    cout << ans;
}
