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
#define pb push_back
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

const int MAX = 1e5 + 5;

struct query {
	int v, k, idx;
	bool operator<(query a) const {
		return k > a.k;
	}
};

int n, m;
int x[MAX];
vt<int> adj[MAX];
vt<query> q[MAX];
int ans[MAX];

void input() {
	cin >> n >> m;
	FOR(i, 1, n + 1) cin >> x[i];
	FOR(n - 1) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	FOR(m) {
		int v, k;
		cin >> v >> k;
		q[v].pb({ v, k, i });
	}
}

int par[MAX];
vt<int> chd[MAX];

void dfs(int v, int prv) {
	par[v] = prv;
	EACH(u, adj[v]) {
		if (u == prv) continue;
		chd[v].push_back(u);
		dfs(u, v);
	}
}

priority_queue<int, vt<int>, greater<int>> f(int v) {
	priority_queue<int, vt<int>, greater<int>> ret;

	ret.push(x[v]);

	EACH(u, chd[v]) {
		priority_queue<int, vt<int>, greater<int>> res = f(u);
		while (res.size()) {
			ret.push(res.top());
			res.pop();
		}
	}

	while (ret.size() > 20) ret.pop();

	//
	sort(all(q[v]));

	auto pq = ret;

	EACH(i, q[v]) {
		while (pq.size() > i.k) pq.pop();
		ans[i.idx] = pq.top();
	}

	return ret;
}

void solve() {
	input();

	dfs(1, 0);

	f(1);

	FOR(m) cout << ans[i] << '\n';
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
