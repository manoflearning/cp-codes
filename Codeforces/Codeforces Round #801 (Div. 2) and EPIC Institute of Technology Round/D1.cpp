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

int n, rt = -1;
vt<int> adj[202020];
ll dep[202020], depv[202020];

void init() {
	rt = -1;
	FOR(n + 1) {
		adj[i].clear();
		dep[i] = 0;
		depv[i] = 0;
	}
	n = 0;
}

void dfs(int v, int prv) {
	if (sz(adj[v]) == 1) depv[dep[v]]++;

	EACH(i, adj[v]) {
		if (i == prv) continue;

		if (sz(adj[v]) == 2) {
			dep[i] = dep[v];
		}
		else {
			dep[i] = v;
		}
		dfs(i, v);
	}
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

	int tc; cin >> tc;
	while (tc--) {
		cin >> n;

		// 예외 처리 1: 답이 0인 경우
		if (n == 1) {
			cout << 0 << '\n';
		}
		else {
			FOR(n - 1) {
				int u, v;
				cin >> u >> v;
				adj[u].push_back(v);
				adj[v].push_back(u);
			}

			int cnt1 = 0, cnt2 = 0;
			FOR(i, 1, n + 1) {
				if (sz(adj[i]) == 1) cnt1++;
				if (sz(adj[i]) == 2) cnt2++;
				if (sz(adj[i]) >= 3 && rt == -1) rt = i;
			}

			// 예외 처리 2: 답이 1인 경우
			if (cnt1 == 2 && cnt2 == n - 2) {
				cout << 1 << '\n';
			}
			// 이제 답은 항상 2 이상이다
			else {
				dfs(rt, 0);
				ll ans = 0;
				FOR(i, n + 1) {
					if (depv[i] >= 2) ans += depv[i] - 1;
					else ans += depv[i];
				}
				cout << ans << '\n';
			}
		}

		init();
	}

	return 0;
}