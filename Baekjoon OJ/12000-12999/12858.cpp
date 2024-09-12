#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void add(int p, ll val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1) {
            t[p >> 1] = gcd(t[p], t[p ^ 1]);
        }
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return abs(t[n]);
        int mid = (nl + nr) >> 1;
        return gcd(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

struct LazySeg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
	}
	// add a value to all elements in interval [l, r]
	void add(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		add(l, r, value, n << 1, nl, mid);
		add(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}
			t[n] += lazy[n] * (nr - nl + 1);
			lazy[n] = 0;
		}
	}
}lzseg;


int n, q;
vector<ll> a(MAXN);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    seg.build(n);
    lzseg.build(n);
    for (int i = 1; i <= n; i++) {
        if (1 < i) seg.add(i, a[i] - a[i - 1]);
        lzseg.add(i, i, a[i]);
    }

    cin >> q;
    while (q--) {
        ll t; int l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            cout << abs(gcd(lzseg.query(l, l), seg.query(l + 1, r))) << '\n';
        } else {
            seg.add(l, t);
            seg.add(r + 1, -t);
            lzseg.add(l, r, t);
        }
    }
}
