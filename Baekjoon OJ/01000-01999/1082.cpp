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

#define EXPAND( x ) x // Use this if Microsoft Visual Studio doesn't expand __VA_ARGS__ correctly
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

struct bi {
	ll d18[3];
	int mxd, v;
	
	bool operator<(bi a) const {
		if (mxd != a.mxd) return mxd < a.mxd;
		if (d18[2] != a.d18[2]) return d18[2] < a.d18[2];
		if (d18[1] != a.d18[1]) return d18[1] < a.d18[1];
		return d18[0] < a.d18[0];
	}

	void add(int x) {
		mxd++;
		d18[mxd / 18] += x * (ll)pow(10, mxd % 18);
	}

	void print() {
		FOR(i, mxd / 18, -1, -1) {
			if (i == mxd / 18) cout << d18[i];
			else {
				FOR(j, 17, -1, -1) {
					cout << d18[i] / (ll)pow(10, j) % 10;
				}
			}
		}
	}
};

int n, p[10], m;
bi dp[55];

void init() {
	FOR(15) {
		dp[i].mxd = -1;
		dp[i].v = 0;
	}
}

void input() {
	cin >> n;
	FOR(n) cin >> p[i];
	cin >> m;
}

bi f(int co) {
	bi& ret = dp[co];
	if (ret.v) return ret;

	ret.v = 1;

	FOR(n) {
		if (p[i] <= co) {
			bi res = f(co - p[i]);
			res.add(i);
			ret = max(ret, res);
		}
	}

	return ret;
}

void solve() {
	init();

	input();

	bi ans = f(m);
	if (!ans.d18[ans.mxd / 18]) ans.mxd = -1;

	for (int i = 1; i < n; i++) {
		if (p[i] <= m) {
			bi res = f(m - p[i]);
			res.add(i);
			ans = max(ans, res);
		}
	}
	
	ans.print();
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
