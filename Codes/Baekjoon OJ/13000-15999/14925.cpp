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

int m, n, a[1010][1010];
int dp[1010][1010];

void init() {
	FOR(1010) {
		memset(dp[i], -1, sizeof(dp[i]));
	}
}

void input() {
	cin >> m >> n;
	FOR(y, m) {
		FOR(x, n) {
			cin >> a[y][x];
		}
	}
}

int f(int y, int x) {
	int& ret = dp[y][x];
	if (ret != -1) return ret;
	if (a[y][x]) return ret = 0;
	if (!y || !x) return ret = 1;

	ret = min({ f(y - 1, x - 1), f(y, x - 1), f(y - 1, x) }) + 1;

	return ret;
}

void solve() {
	init();

	input();

	int ans = 0;
	FOR(y, m) {
		FOR(x, n) {
			ans = max(ans, f(y, x));
		}
	}

	cout << ans;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}