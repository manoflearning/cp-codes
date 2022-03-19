// set
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

int n, q, now = 1;
set<int> s;

void input() {
	cin >> n >> q;
	FOR(n) {
		int x; cin >> x;
		if (x) s.insert(i + 1);
	}
}

void f() {
	FOR(q) {
		int x, y;
		cin >> x;
		if (x < 3) cin >> y;

		if (x == 1) {
			if (s.find(y) == s.end()) s.insert(y);
			else s.erase(y);
		}
		if (x == 2) {
			y %= n;
			now += y;
			if (now > n) now -= n;
		}
		if (x == 3) {
			auto it = s.lower_bound(now);
			if (it == s.end()) it = s.lower_bound(1);
			
			if (it == s.end()) cout << -1 << '\n';
			else {
				if (now <= *it) cout << *it - now << '\n';
				else cout << n - now + *it << '\n';
			}
		}
	}
}

void solve() {
	input();

	f();
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}

// segment tree
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

struct Seg {
	int flag;  // array size
	vector<ll> t;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);

		for (int i = flag; i < flag + N; i++) {
			int x; cin >> x;
			if (x) t[i] = i - flag + 1;
			else t[i] = INF;
		}
		for (int i = flag - 1; i >= 1; i--) t[i] = min(t[i << 1], t[i << 1 | 1]);
	}
	void modify(int p) {  // set value at position p
		if (t[p + flag - 1] == INF) t[p + flag - 1] = p;
		else t[p + flag - 1] = INF;

		for (p += flag - 1; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r) {
		return query(l, r, 1, 1, flag);
	}
	ll query(int l, int r, int n, int nl, int nr) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int n, q, now = 1;

void input() {
	cin >> n >> q;
	seg.build(n);
}

void f() {
	FOR(q) {
		int x, y;
		cin >> x;
		if (x < 3) cin >> y;

		if (x == 1) seg.modify(y);
		if (x == 2) {
			y %= n;
			now += y;
			if (now > n) now -= n;
		}
		if (x == 3) {
			int x = seg.query(now, n) - now;
			if (x > n) x = (n - now) + seg.query(1, now - 1);

			if (x > n) cout << -1 << '\n';
			else cout << x << '\n';
		}
	}
}

void solve() {
	input();

	f();
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}*/
