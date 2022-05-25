#define _USE_MATH_DEFINES
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

const int MAXD = 18;

struct wv {
	ll w;
	int v;
};

struct uv {
	int u, v;
};

int n;
ll sub[505050];
int dep[505050], par[505050][MAXD + 5];
vt<wv> adj[505050];
vt<uv> edge[505050];
ll ans;

int dfs(int now, int prv) {
	par[now][0] = prv;
	dep[now] = dep[prv] + 1;
	sub[now] = 1;

	for (auto i : adj[now]) {
		if (i.v == prv) continue;
		sub[now] += dfs(i.v, now);
	}
	return sub[now];
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);

	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) u = par[u][i];

	if (u == v) return u;

	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	// input
	cin >> n;
	FOR(n - 1) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
		adj[v].push_back({ w, u });
		edge[w].push_back({ u, v });
	}

	// lca
	dfs(1, 0);

	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
	}

	//
	FOR(i, 1, n + 1) {
		EACH(j, edge[i]) {
			if (dep[j.u] < dep[j.v]) swap(j.u, j.v);
		}

		if (sz(edge[i]) == 1) {
			int u = edge[i][0].u;
			ans += sub[u] * (n - sub[u]);
		}
		if (sz(edge[i]) >= 2) {
			EACH(j, edge[i]) {
				int u = j.u;


			}
		}
	}

	cout << ans;

	return 0;
}