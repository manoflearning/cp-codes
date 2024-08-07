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

int n, m;
int c[303030];
ll cost[44], sum[44];
vt<pll> choice[44];
int vi[44];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= m; i++) cin >> cost[i];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	for (int v = 1; v <= n; v++) {
		int nxt1 = c[v + 1];
		int nxt2 = c[v + 2];

		if (nxt1 == c[v] || nxt2 == c[v]) continue;

		choice[c[v]].push_back({ min(nxt1, nxt2), max(nxt1, nxt2) });
	}

	for (int v = 1; v <= m; v++) {
		sort(all(choice[v]));
		choice[v].erase(unique(all(choice[v])), choice[v].end());
	}

	for (int v = 1; v <= n; v++) {
		sum[c[v]] += cost[c[v]];
	}

	vi[c[1]] = 1;
	vi[c[n]] = 1;

	cout << f() + sum[c[1]] + (c[1] != c[n] ? sum[c[n]] : 0);

	return 0;
}