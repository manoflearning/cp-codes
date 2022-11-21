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

int vi[2525][2525];
double dp[2525][2525];

double f(int lb, int rb, int x) {
	// [lb, rb]에서 x 찾기
	// iff [1, rb - lb + 1]에서 x - lb + 1 찾기

	int len = rb - lb + 1, k = x - lb + 1;
	double& ret = dp[len][k];

	if (vi[len][k]) return ret;
	if (lb == rb) return ret = 1;

	vi[len][k] = 1;

	int s = max(1, len / 2);
	int e = min(len, (len + 1) / 2 + 1);
	for (int i = s; i <= e; i++) {
		if (i == k) ret += (double)1 / (e - s + 1);
		else {
			if (i < k) ret += (double)1 / (e - s + 1) * (1 + f(i + 1, len, k));
			else ret += (double)1 / (e - s + 1) * (1 + f(1, i - 1, k));
		}
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

    cout << fixed;
    cout.precision(10);
	
	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		int x, y, k;
        cin >> x >> y >> k;

        cout << f(x, y, k) << '\n';
	}

	return 0;
}