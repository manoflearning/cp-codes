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

ll n, a[303030];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	// 0 등장 횟수
	ll ans = 0;
	for (ll x = 1; x <= n; x++) {
		if (a[x] == 0) ans += x * (n - x + 1);
	}

	// 기본 1개
	ans += n * (n + 1) / 2;

	ll l = 1;
	for (ll r = 1; r <= n; r++) {
		if (a[r]) {
			l = r + 1;
			continue;
		}

		ans -= (r - l + 1);
	}
	
	// 추가 1개
	vt<pll> arr;
	ll prv1 = -1, prv2 = -1;
	for (ll x = 1; x <= n; x++) {
		if (a[x] == 3) {
			prv1 = prv2 = -1;
			continue;
		}
		
		if (a[x] == 1) {
			prv1 = x;
			if (prv2 != -1) {
				arr.push_back({ prv2, prv1 });
			}
		}
		if (a[x] == 2) {
			prv2 = x;
			if (prv1 != -1) {
				arr.push_back({ prv1, prv2 });
			}
		}
	}

	for (int i = 0; i < sz(arr); i++) {
		for (int j = i; j < sz(arr); j++) {
			if (j - i >= 2) break;

			ll l = arr[i].fr, r = arr[j].sc;

			if ((j - i) & 1) {
				ans -= (n - r + 1) * l;
			}
			else {
				ans += (n - r + 1) * l;
			}
		}
	}

	cout << ans;

	return 0;
}