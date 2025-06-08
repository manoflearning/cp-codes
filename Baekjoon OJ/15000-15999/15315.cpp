#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 202020;
const int MOD = 1e9 + 7;

inline ll add_mod(ll x, ll y) { return ((x + y) % MOD + MOD) % MOD; }
inline ll mul_mod(ll x, ll y) { return (x * y % MOD + MOD) % MOD; }
ll pow_mod(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = pow_mod(x, y / 2);
    return mul_mod(mul_mod(res, res), y & 1 ? x : 1);
}

int n;
ll a, b, p, np;
vector<int> adj[N];
ll dp1[N], dp[N], ans;

void dfs1(int v, int prv) {
    dp1[v] = np;
    for (auto &i : adj[v]) {
        if (i == prv) continue;
        dfs1(i, v);
        dp1[v] = add_mod(
            dp1[v], 
            mul_mod(np, dp1[i])
        );
    }
}

void dfs2(int v, int prv) {
    dp[v] = dp1[v];

    if (prv != 0) {
        ll dp_prv = add_mod(dp[prv], -mul_mod(np, dp1[v]));
        dp[v] = add_mod(dp[v], mul_mod(np, dp_prv));
    }

    ll acc = 0;
    for (auto &i : adj[v]) {
        if (i == prv) continue;
        dfs2(i, v);
        
        ll e_v = add_mod(dp[v], -mul_mod(np, dp1[i]));
        ll e_i = dp1[i];

        ll res = mul_mod(e_v, e_i);
        acc = add_mod(acc, res);
    }

    ans = add_mod(ans, acc);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> a >> b;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    p = mul_mod(a, pow_mod(b, MOD - 2));
    np = add_mod(1, -p);

    dfs1(1, 0);
    dfs2(1, 0);

    cout << ans;
}