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

int n;
vt<string> a;

int f(int sy, int sx) {
	int c1 = INF, c2 = INF, c3 = INF, c4 = INF;

	if (sy + 5 < n) {
		c1 = 0;
		c1 += (a[sy][sx] == '.');
		c1 += (a[sy + 1][sx] == '.');
		c1 += (a[sy + 2][sx] == '.');
		c1 += (a[sy + 3][sx] == '.');
		c1 += (a[sy + 4][sx] == '.');
		c1 += (a[sy + 5][sx] == '.');
	}
	
	if (sx + 5 < n) {
		c2 = 0;
		c2 += (a[sy][sx] == '.');
		c2 += (a[sy][sx + 1] == '.');
		c2 += (a[sy][sx + 2] == '.');
		c2 += (a[sy][sx + 3] == '.');
		c2 += (a[sy][sx + 4] == '.');
		c2 += (a[sy][sx + 5] == '.');
	}

	if (sy + 5 < n && sx + 5 < n) {
		c3 = 0;
		c3 += (a[sy][sx] == '.');
		c3 += (a[sy + 1][sx + 1] == '.');
		c3 += (a[sy + 2][sx + 2] == '.');
		c3 += (a[sy + 3][sx + 3] == '.');
		c3 += (a[sy + 4][sx + 4] == '.');
		c3 += (a[sy + 5][sx + 5] == '.');
	}

	if (sy + 5 < n && 0 <= sx - 5) {
		c4 = 0;
		c4 += (a[sy][sx] == '.');
		c4 += (a[sy + 1][sx - 1] == '.');
		c4 += (a[sy + 2][sx - 2] == '.');
		c4 += (a[sy + 3][sx - 3] == '.');
		c4 += (a[sy + 4][sx - 4] == '.');
		c4 += (a[sy + 5][sx - 5] == '.');
	}

	return (c1 <= 2) || (c2 <= 2) || (c3 <= 2) || (c4 <= 2);
}

void solve() {
	cin >> n;
	a.resize(n);
	EACH(i, a) cin >> i;

	int ans = 0;

	FOR(y, n) {
		FOR(x, n) {
			if (f(y, x)) ans = 1;
		}
	}

	if (ans) cout << "Yes";
	else cout << "No";
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
