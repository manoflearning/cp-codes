// dynamic programming
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

int n;
ll a[101010], dp[101010][2];

void input() {
	cin >> n;
	FOR(n) cin >> a[i];
}

ll f() {
	ll ret = a[0];

	dp[0][0] = a[0];
	FOR(i, 1, n) {
		dp[i][0] = max(a[i], dp[i - 1][0] + a[i]);
		dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + a[i]);

		ret = max({ ret, dp[i][0], dp[i][1] });
	}

	return ret;
}

void solve() {
	input();

	cout << f();
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}

// divide and conquer
/*#define _USE_MATH_DEFINES
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

int n;
vt<ll> a;

void input() {
	cin >> n;
	a.resize(n + 1);
	FOR(i, 1, n + 1) cin >> a[i];
}

ll f(int l, int r) {
	if (l == r) return a[l];

	int mid = (l + r) >> 1;

	ll mxl0 = a[mid], mxl1 = -INF, mxr0 = a[mid + 1], mxr1 = -INF;
	ll suml = 0, sumr = 0, mnl = 0, mnr = 0;

	FOR(i, mid, l - 1, -1) {
		mnl = min(mnl, a[i]);

		suml += a[i];

		if (mxl0 < suml) mxl0 = suml;
		if (i < mid && mxl1 < suml - mnl) mxl1 = suml - mnl;
	}

	FOR(i, mid + 1, r + 1) {
		mnr = min(mnr, a[i]);

		sumr += a[i];

		if (mxr0 < sumr) mxr0 = sumr;
		if (mid + 1 < i && mxr1 < sumr - mnr) mxr1 = sumr - mnr;
	}

	ll res = max({ mxl0 + mxr0, mxl1 + mxr0, mxl0 + mxr1 });

	return max({ res, f(l, mid), f(mid + 1, r) });
}

void solve() {
	input();

	cout << f(1, n);
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}*/
