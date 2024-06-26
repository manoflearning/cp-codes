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

const int MAX = 1e3 + 5;

int n, a[MAX][MAX];

void input() {
	cin >> n;
	FOR(n) {
		FOR(j, n) {
			char c; cin >> c;
			if (c == 'R') a[i][j] = 1;
		}
	}
}

int find() {
	FOR(n) {
		int cnt1 = 0, cnt2 = 0;
		FOR(j, n) {
			if (i > 0 && a[i - 1][j] != a[i][j]) cnt1++;
			if (i < n - 1 && a[i + 1][j] != a[i][j]) cnt2++;
		}

		if (cnt1 == n) cnt1 = 0;
		if (cnt2 == n) cnt2 = 0;

		if (!cnt1 && !cnt2) return i;
	}
	return -1;
}

void f() {
	int flag = find();
	
	if (flag == -1) {
		cout << -1;
		return;
	}

	int prv = flag;
	set<int> cnt2;

	FOR(n) {
		if (flag == i) continue;

		int cnt = 0;
		
		FOR(j, n) {
			if (a[prv][j] != a[i][j]) cnt++;
		}

		if (2 * cnt > n) {
			cnt = n - cnt;
			FOR(j, n) a[i][j] = !a[i][j];
		}

		if (cnt >= 2) {
			cout << -1;
			return;
		}

		if (cnt == 1) {
			cnt2.insert(prv);
			cnt2.insert(i);
		}

		prv = i;
	}

	if (cnt2.empty() || cnt2.size() > 3) {
		cout << -1;
		return;
	}

	EACH(i, cnt2) {
		FOR(j, n) {
			if (a[flag][j] != a[i][j]) {
				cout << i + 1 << ' ' << j + 1;
				return;
			}
		}
	}
}

void f2() {
	int cnt = (a[0][0] != a[1][0]) + (a[0][1] != a[1][1]);

	if (cnt == 1) {
		if (a[0][0] != a[0][1]) cout << 1 << ' ' << 1;
		else cout << 2 << ' ' << 1;
	}
	else cout << -1;
}

void solve() {
	input();

	if (n == 2) f2();
	if (n >= 3) f();
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
