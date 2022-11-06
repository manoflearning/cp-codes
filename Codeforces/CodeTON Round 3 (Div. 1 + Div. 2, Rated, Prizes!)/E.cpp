#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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

int n, psum[202020];
string s;

void init() {

}

void input() {
	cin >> n >> s;
	s.push_back('0');
	for (int i = n - 1; i >= 0; i--) {
		s[i + 1] = s[i];
	}
}

void buildPsum() {
	for (int i = 1; i <= n; i++) {
		if (s[i] == '(') psum[i] = psum[i - 1] + 1;
		else psum[i] = psum[i - 1];
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		init();
		
		input();

		buildPsum();
		
		ll ans = 0;
		for (int l = 1; l <= n; l++) {
			for (int r = l; r <= n; r++) {
				int sum = (psum[r] - psum[l - 1]);
				ans += max(sum, (r - l + 1) - sum);
			}
		}

		stack<ll> stk;
		for (ll i = 1; i <= n; i++) {
			if (s[i] == '(') stk.push(i);
			else {
				if (stk.empty()) continue;
				ans -= stk.top() * (n - i + 1);
				stk.pop();
			}
		}

		cout << ans << '\n';
	}

	return 0;
}