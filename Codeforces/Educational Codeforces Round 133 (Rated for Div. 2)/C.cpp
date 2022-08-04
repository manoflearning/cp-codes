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
struct Seg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
        t.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);

		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg1l, seg1r, seg2l, seg2r;

int n;
ll a[3][202020];
ll dp[3][202020];

void init() {
    FOR(i, 1, n + 1) {
        a[1][i] = a[2][i] = dp[1][i] = dp[2][i] = 0;
    }
    n = 0;
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
    FOR(tt, 1, tc + 1) {
        int n; cin >> n;
        FOR(i, 1, 3) FOR(j, 1, n + 1) {
            cin >> a[i][j];
            a[i][j]++;
        }
        a[1][1] = 0;

        dp[1][1] = 0;
        dp[2][1] = max(1ll, a[2][1]);

        FOR(i, 2, n + 1) {
            if (i & 1) {
                dp[1][i] = max(a[1][i], dp[1][i - 1] + 1);
                dp[2][i] = max(a[2][i], dp[1][i] + 1);
            }
            else {
                dp[2][i] = max(a[2][i], dp[2][i - 1] + 1);
                dp[1][i] = max(a[1][i], dp[2][i] + 1);
            }
        }

        seg1l.build(n);
        seg1r.build(n);
        seg2l.build(n);
        seg2r.build(n);
        
        FOR(i, 1, n + 1) {
            seg1l.modify(i, a[1][i] + (n - i));
            seg1r.modify(i, a[1][i] + (i - 1));
            seg2l.modify(i, a[2][i] + (n - i));
            seg2r.modify(i, a[2][i] + (i - 1));
        }

        ll ans = (n & 1 ? dp[2][n] : dp[1][n]);
        FOR(i, 1, n + 1) {
            if (i & 1) {
                ll res = seg1l.query(i, n) + (n - i + 1);
                res = max(res, seg2r.query(i, n) - i + 1);
                //cout << i << ' ' << seg1l.query(i, n) << ' ' << seg2r.query(i, n) - i + 1 << '\n';
                ans = min(ans, max(dp[1][i] + 2 * (n - i + 1) - 1, res));
            }
            else {
                ll res = seg2l.query(i, n) + (n - i + 1);
                res = max(res, seg1r.query(i, n) - i + 1);
                //cout << i << ' ' << seg2l.query(i, n) << ' ' << seg1r.query(i, n) - i + 1 << '\n';
                ans = min(ans, max(dp[2][i] + 2 * (n - i + 1) - 1, res));
            }
        }

        cout << ans << '\n';

        init();
    }

	return 0;
}