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

int flag;  // array size
struct Seg {  // 1-based
	vector<ll> t, lazy;

	void build(int n) {
        t.clear(); lazy.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);

		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);

		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n, nl, nr);
			return;
		}

		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);

		t[n] = max(t[n << 1], t[n << 1 | 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);

		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}
			t[n] += lazy[n];
			lazy[n] = 0;
		}
	}
}seg;

struct point {
    ll y, x;
    bool operator<(const point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

struct lineSeg {
    ll x, ys, ye;
    int isO;

    bool operator<(const lineSeg& rhs) const {
        return x < rhs.x;
    }
};

int n, mxy;
vt<vt<point>> a;
vt<lineSeg> b;

void init() {
    n = mxy = 0;
    a.clear();
    b.clear();
}

void input() {
    cin >> n;
    FOR(n) {
        int k; cin >> k;
        vt<point> res;
        FOR(j, k) {
            int y, x;
            cin >> x >> y;
            res.push_back({ y, x });
        }
        a.push_back(res);
    }
}

void cc() {
    vt<int> c;
    EACH(i, a) {
        EACH(j, i) c.push_back(j.y);
    }

    sort(all(c));
    c.erase(unique(all(c)), c.end());
    mxy = sz(c);

    EACH(i, a) {
        EACH(j, i) j.y = lower_bound(all(c), j.y) - c.begin() + 1;
    }
}

void getLineSeg() {
    seg.build(mxy);

    EACH(i, a) {
        sort(all(i));

        FOR(j, sz(i) - 1) {
            if (i[j].x == i[j + 1].x) {
                int bit = 1;
                if (seg.query(i[j].y, i[j + 1].y - 1) == 0) {
                    b.push_back({ i[j].x, i[j].y, i[j + 1].y, 1 });
                    seg.modify(i[j].y, i[j + 1].y - 1, 1);
                }
                else {
                    b.push_back({ i[j].x, i[j].y, i[j + 1].y, 0 });
                    seg.modify(i[j].y, i[j + 1].y - 1, -1);
                }

                if (j + 2 < sz(i) && i[j + 1].x == i[j + 2].x) j++;
            }
        }
    }

    sort(all(b));

    //EACH(i, b) cout << i.x << ' ' << i.ys << ' ' << i.ye << ' ' << i.isO << '\n';
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

	int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        cc();

        getLineSeg();

        //seg.build(mxy);

        ll ans = 0;
        EACH(i, b) {
            if (i.isO) {
                //cout << i.x << ' ' << i.ys << ' ' << i.ye << ' ' << i.isO << '\n';
                //cout << seg.query(i.ys, i.ye - 1) + 1 << '\n';
                ans = max(ans, seg.query(i.ys, i.ye - 1) + 1);
            }
            seg.modify(i.ys, i.ye - 1, i.isO ? 1 : -1);
        }
        cout << ans << '\n';
    }

	return 0;
}