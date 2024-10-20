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
pll a[12], b[5];
pll loc[18];

ll p2[7];

double dp[1 << 12][1 << 5][18];
int vi[1 << 12][1 << 5][18];

int countBit(int bit) {
	int ret = 0;
	FOR(m) if (bit & (1 << i)) ret++;
	return ret;
}

double dist(ll x, ll y, ll nx, ll ny, ll cnt) {
	return sqrt((x - nx) * (x - nx) + (y - ny) * (y - ny)) / p2[cnt];
}

double f(int bita, int bitb, int now) {
	double& ret = dp[bita][bitb][now];
	if (vi[bita][bitb][now]) return ret;
	
	vi[bita][bitb][now] = 1;

	ll x = loc[now].fr, y = loc[now].sc;

	ll cnt = countBit(bitb);

	ret = 1e18;
	if (bita == (1 << n) - 1) {
		ret = min(ret, dist(x, y, 0, 0, cnt));
	}

	FOR(n) {
		if (bita & (1 << i)) continue;
		ll nx = a[i].fr, ny = a[i].sc;
		ret = min(ret, dist(x, y, nx, ny, cnt) + f(bita | (1 << i), bitb, i));
	}

	FOR(m) {
		if (bitb & (1 << i)) continue;
		ll nx = b[i].fr, ny = b[i].sc;
		ret = min(ret, dist(x, y, nx, ny, cnt) + f(bita, bitb | (1 << i), i + n));
	}

	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	p2[0] = 1;
	FOR(i, 1, 6) p2[i] = (p2[i - 1] << 1);

	cin >> n >> m;
	FOR(n) {
		cin >> a[i].fr >> a[i].sc;
		loc[i].fr = a[i].fr;
		loc[i].sc = a[i].sc;
	}
	FOR(m) {
		cin >> b[i].fr >> b[i].sc;
		loc[i + n].fr = b[i].fr;
		loc[i + n].sc = b[i].sc;
	}
	loc[n + m] = { 0, 0 };

	cout << fixed;
	cout.precision(10);

	cout << f(0, 0, n + m);

	return 0;
}