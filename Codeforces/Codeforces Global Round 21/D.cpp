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

struct val {
    ll x, idx;
    bool operator<(const val& rhs) const {
        return x < rhs.x;
    }
};

struct mxSeg {  // 0-based
	int n;  // array size
	val t[505050];

	void build(int N, const vt<int>& a) {
		n = N;
		for (int i = 0; i < n; i++) t[n + i] = { a[i + 1], i + 1 };
		for (int i = n - 1; i >= 1; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
	}
	/*void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}*/
	val query(int l, int r) {  // sum on interval [l, r)
		val ret = { 0, 0 };
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, t[l++]);
			if (r & 1) ret = max(ret, t[--r]);
		}
		return ret;
	}
}mxseg;

struct mnSeg {  // 0-based
	int n;  // array size
	val t[505050];

	void build(int N, const vt<int>& a) {
		n = N;
		for (int i = 0; i < n; i++) t[n + i] = { a[i + 1], i + 1 };
		for (int i = n - 1; i >= 1; i--) t[i] = min(t[i << 1], t[i << 1 | 1]);
	}
	/*void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}*/
	val query(int l, int r) {  // sum on interval [l, r)
		val ret = { INF, 0 };
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, t[l++]);
			if (r & 1) ret = min(ret, t[--r]);
		}
		return ret;
	}
}mnseg;

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
        int n; cin >> n;
        vt<int> a(n + 1);
        FOR(n) cin >> a[i + 1];

        mxseg.build(n, a);
        mnseg.build(n, a);

        int ans = 0, now = 1;
        while (now ^ n) {
            if (a[now] < a[now + 1]) {
                int l = now, r = n;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (a[now] > mnseg.query(now - 1, mid).x) r = mid - 1;
                    else l = mid;
                }
                now = mxseg.query(now - 1, l).idx;
            }
            else {
                int l = now, r = n;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (a[now] < mxseg.query(now - 1, mid).x) r = mid - 1;
                    else l = mid;
                }
                now = mnseg.query(now - 1, l).idx;
            }

            ans++;
        }

        cout << ans << '\n';
    }

	return 0;
}