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

int k, m;
ll val, pk[11];
vt<ll> a;
vt<pll> e;

int N, M;
vt<int> adj[5050505], vi[5050505];
int ind[5050505], outd[5050505], nxt[5050505];
vt<int> ans;

void com(int idx) {
	if (idx == m) {
		a.push_back(val);
		return;
	}

	FOR(i, k) {
		val += i;
		val *= k;
		com(idx + 1);
		val /= k;
		val -= i;
	}
}

void makingGraph() {
	FOR(sz(a)) {
		int v = a[i] % pk[m - 1], u = a[i] - (a[i] % pk[1]);

		e.push_back({ v, u });
	}

	N = pk[m - 1], M = sz(e);
	FOR(M) {
		adj[e[i].fr].push_back(e[i].sc);
		ind[e[i].sc]++;
		outd[e[i].fr]++;
	}
}

int doesCircuitExist() {
	FOR(N) {
		if (ind[i] != outd[i]) return 0;
	}
	return 1;
}

void dfs(int now) {
	for (int& i = nxt[now]; i < sz(adj[now]); i++) {
		if (i < sz(adj[now]) && !vi[now][i]) {
			vi[now][i] = 1;
			dfs(adj[now][i]);
		}
	}
	ans.push_back(now);
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
	
	cin >> k >> m;

	pk[0] = 1;
	for (int i = 1; i <= m; i++) {
		pk[i] = pk[i - 1] * k;
	}

	com(0);

	// if m = 1
	if (m == 1) {
		EACH(i, b) cout << i[0] << ' ';
		return 0;
	}

	// otherwise
	cc();

	makingGraph();

	if (!doesCircuitExist()) {
		cout << -1;
		return 0;
	}

	FOR(i, N) vi[i].resize(sz(adj[i]));

	dfs(0);
	
	EACH(i, c[ans[0]]) cout << i << ' ';
	FOR(i, 1, sz(ans)) cout << c[ans[i]].back() << ' ';

	return 0;
}