#pragma GCC optimize("O3")

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

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);

		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int q;
vt<pll> a;
vt<ll> c;
vt<int> vi;
ll ans;

void cc() {
    c.push_back(-INF);
    EACH(i, a) {
        c.push_back(i.sc - 1);
        c.push_back(i.sc);
        c.push_back(i.sc + 1);
    }

    sort(all(c));
    c.erase(unique(all(c)), c.end());

    EACH(i, a) {
        i.sc = lower_bound(all(c), i.sc) - c.begin();
    }
}

void bsl(ll& ls, ll& le, ll idx) {
    while (ls < le) {
        ll mid = (ls + le) >> 1;
        ll len = idx - mid + 1;
        
        if (seg.query(mid, idx) == len) le = mid;
        else ls = mid + 1;
    }
}

void bsr(ll& rs, ll& re, ll idx) {
    while (rs < re) {
        ll mid = (rs + re + 1) >> 1;
        ll len = mid - idx + 1;
        
        if (seg.query(idx, mid) == len) rs = mid;
        else re = mid - 1;
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> q;
    a.resize(q);
    EACH(i, a) cin >> i.fr >> i.sc;

    cc();

    vi.resize(sz(c));
    seg.build(sz(c));

    EACH(i, a) {
        if (i.fr == 1) {
            vi[i.sc] = 1;
            seg.modify(i.sc, 1);

            ll ls = 1, le = i.sc - 1;
            ll rs = i.sc + 1, re = sz(c) - 1;
            
            if (vi[i.sc - 1]) bsl(ls, le, i.sc - 1);
            else ls = le = i.sc;

            if (vi[i.sc + 1]) bsr(rs, re, i.sc + 1);
            else rs = re = i.sc;

            ll llen = (i.sc - 1 - ls + 1);
            ll rlen = (re - (i.sc + 1) + 1);

            if (ls != i.sc) ans -= llen * (llen - 1) / 2 + llen;
            if (rs != i.sc) ans -= rlen * (rlen - 1) / 2 + rlen;
            ans += (re - ls + 1) * (re - ls) / 2 + (re - ls + 1);
        }
        else {
            vi[i.sc] = 0;
            seg.modify(i.sc, 0);

            ll ls = 1, le = i.sc - 1;
            ll rs = i.sc + 1, re = sz(c) - 1;
            
            if (vi[i.sc - 1]) bsl(ls, le, i.sc - 1);
            else ls = le = i.sc;

            if (vi[i.sc + 1]) bsr(rs, re, i.sc + 1);
            else rs = re = i.sc;
            
            ll llen = (i.sc - 1 - ls + 1);
            ll rlen = (re - (i.sc + 1) + 1);
            
            if (ls != i.sc) ans += llen * (llen - 1) / 2 + llen;
            if (rs != i.sc) ans += rlen * (rlen - 1) / 2 + rlen;
            ans -= (re - ls + 1) * (re - ls) / 2 + (re - ls + 1);
        }

        cout << ans << '\n';
    }

	return 0;
}