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

ll m, k;
ll dp[1300][55][55];

void init() {
	FOR(1300) {
		FOR(j, 55) {
			FOR(k, 55) {
				dp[i][j][k] = -1;
			}
		}
	}
}

ll C(ll n) {
	return n * (n - 1) / 2;
}

ll f(ll p, ll q, ll r) {
	ll& ret = dp[p][q][r];
	if (ret != -1) return ret;
	if (p == 1) return ret = (q == 2 && r == 1 ? C(m) : 0);

	ret = 0;

	if (q - 2 >= 2 && r - 1 >= 1) {
		ret += C(m - (q - 2)) * f(p - 1, q - 2, r - 1) % MOD;
	}

	if (q - 1 >= 2) {
		ret += (q - 1) * (m - (q - 1)) * f(p - 1, q - 1, r) % MOD;
	}

	ret += (C(q) - (p - 1)) * f(p - 1, q, r) % MOD;

	return ret %= MOD;
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

	init();

	int tc; cin >> tc;

	FOR(t, 1, tc + 1) {
		cin >> m >> k;

		cout << "Case #" << t << ": ";
		cout << f(C(m), m, k) << '\n';
	}

	return 0;
}