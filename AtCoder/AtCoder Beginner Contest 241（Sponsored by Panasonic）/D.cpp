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

struct Seg {
	int flag;  // array size
	vector<ll> t;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p) {  // set value at position p
		for (t[p += flag - 1]++; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {
		return query(l, r, 1, 1, flag);
	}
	ll query(int l, int r, int n, int nl, int nr) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

struct qu {
	int op, k;
	ll x;
};

int n;
vt<qu> q;
vt<ll> a;

void input() {
	cin >> n;
	q.resize(n);
	EACH(i, q) {
		cin >> i.op >> i.x;
		if (i.op > 1) cin >> i.k;

		a.push_back(i.x);
	}
}

void comp() {
	a.push_back(0);
	
	sort(all(a));
	a.erase(unique(all(a)), a.end());

	EACH(i, q) {
		i.x = lower_bound(all(a), i.x) - a.begin();
	}
}

void solve() {
	input();

	comp();

	seg.build(sz(a) - 1);

	EACH(i, q) {
		if (i.op == 1) seg.modify(i.x);
		
		if (i.op == 2) {
			int l = 1, r = i.x, sum = seg.query(1, i.x) - i.k + 1;
			while (l < r) {
				int mid = (l + r) >> 1;
				if (seg.query(1, mid) < sum) l = mid + 1;
				else r = mid;
			}

			if (sum > 0 && seg.query(1, l) >= sum) cout << a[l] << '\n';
			else cout << -1 << '\n';
		}
		
		if (i.op == 3) {
			int l = i.x, r = sz(a) - 1, sum = i.k;
			while (l < r) {
				int mid = (l + r) >> 1;
				if (seg.query(i.x, mid) < sum) l = mid + 1;
				else r = mid;
			}
			
			if (seg.query(i.x, l) >= sum) cout << a[l] << '\n';
			else cout << -1 << '\n';
		}
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
