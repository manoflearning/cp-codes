#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 30005;

int n, m, k;
int c[MAX];
vt<int> adj[MAX];

void input() {
	cin >> n >> m >> k;
	FOR(n) cin >> c[i];
	FOR(m) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

ll sum[MAX];
int cnt[MAX], h, visited[MAX];

void dfs(int v) {
	visited[v] = 1;

	sum[h] += c[v];
	cnt[h]++;

	EACH(u, adj[v]) {
		if (visited[u]) continue;
		dfs(u);
	}
}

ll dp[3005];

void f() {
	FOR(h) {
		FOR(j, k - 1, -1, -1) {
			if (j > 0 && !dp[j]) continue;
			if (k <= j + cnt[i]) continue;

			dp[j + cnt[i]] = max(dp[j + cnt[i]], dp[j] + sum[i]);
		}
	}
}

void solve() {
	input();

	FOR(n) {
		if (!visited[i]) {
			dfs(i);
			h++;
		}
	}

	f();

	ll ans = 0;
	FOR(i, 0, k) ans = max(ans, dp[i]);

	cout << ans;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
