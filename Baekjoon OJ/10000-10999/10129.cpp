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

/*int flag;  // array size
struct Seg {  // 1-indexed
    int t[4040404];
    deque<pii> dq[1010101];

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
        for (int i = 0; i < 2 * flag; i++) t[i] = INF;
	}
    void clear() {
        for (int i = 0; i < 1010101; i++)
            while (sz(dq[i])) dq[i].clear();
    }
    void add(int idx, int p, ll val) {
        while (sz(dq[p]) && dq[p].back().fr >= val) dq[p].pop_back();
        dq[p].push_back({ val, idx });
        
        t[p + flag - 1] = (sz(dq[p]) ? dq[p].front().fr : INF);
        
        p += flag - 1;
        for (; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
    }
	void sub(int idx, int p) {  // set value at position p
        if (sz(dq[p]) && dq[p].front().sc == idx) dq[p].pop_front();

        t[p + flag - 1] = (sz(dq[p]) ? dq[p].front().fr : INF);
        
        p += flag - 1;
        for (; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;*/

struct Seg {  // 0-indexed
	int n;  // array size
	int t[2020202];
    deque<pii> dq[1010101];

	void build(int N) {
		n = N;
		for (int i = 0; i < n; i++) t[n + i] = INF;
		for (int i = n - 1; i >= 1; i--) t[i] = min(t[i << 1], t[i << 1 | 1]);
	}
    void clear() {
        for (int i = 0; i < 1010101; i++)
            while (sz(dq[i])) dq[i].clear();
    }
    void add(int idx, int p, ll val) {
        while (sz(dq[p]) && dq[p].back().fr >= val) dq[p].pop_back();
        dq[p].push_back({ val, idx });
        
        t[p + n] = (sz(dq[p]) ? dq[p].front().fr : INF);
        
        p += n;
        for (; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
    }
	void sub(int idx, int p) {  // set value at position p
        if (sz(dq[p]) && dq[p].front().sc == idx) dq[p].pop_front();

        t[p + n] = (sz(dq[p]) ? dq[p].front().fr : INF);
        
        p += n;
        for (; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	int query(int l, int r) {  // sum on interval [l, r)
		int ret = INF;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, t[l++]);
			if (r & 1) ret = min(ret, t[--r]);
		}
		return ret;
	}
}seg;

int n, a[1010101], q;
vt<int> c;

void cc() {
    //c.push_back(-INF);
    FOR(n) c.push_back(a[i + 1]);

    sort(all(c));
    c.erase(unique(all(c)), c.end());

    FOR(i, 1, n + 1) {
        a[i] = lower_bound(all(c), a[i]) - c.begin();
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    FOR(n) cin >> a[i + 1];

    cc();

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        
        seg.build(sz(c));
        seg.add(1, a[1], 0);
        
        for (int i = 2; i <= n; i++) {
            if (i > k + 1) seg.sub(i - (k + 1), a[i - (k + 1)]);
            
            int mn1 = seg.query(0, a[i] - 1) + 1, mn2 = seg.query(a[i] + 1, sz(c) - 1);

            seg.add(i, a[i], min(mn1, mn2));

            if (i == n) cout << min(mn1, mn2) << '\n';
        }

        seg.clear();
    }

	return 0;
}