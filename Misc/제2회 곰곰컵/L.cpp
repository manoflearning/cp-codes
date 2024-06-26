#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll powxy(ll x, ll y) { 
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = powxy(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int n, m, ind[202020], siz[202020];
vector<int> adj[202020];
ll fac[202020];

ll dfs(int v) {
    ll ret = 1;
    siz[v] = 1;
    
    vector<ll> arr;
    for (auto& i : adj[v]) {
        ret = ret * dfs(i) % MOD;
        arr.push_back(siz[i]);
        siz[v] += siz[i];
    }

    ret = ret * fac[siz[v] - 1] % MOD;
    for (auto& i : arr) {
        ret = ret * powxy(fac[i], MOD - 2) % MOD;
    }
    //cout << v << ' ' << ret << '\n';
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    fac[0] = fac[1] = 1;
    for (int i = 2; i < 202020; i++) {
        fac[i] = i * fac[i - 1] % MOD;
    }

	cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        ind[v]++;
    }

    for (int v = 1; v <= n; v++) {
        if (!ind[v]) {
            adj[0].push_back(v);
            ind[v]++;
        }
    }

    cout << dfs(0);

	return 0;
}