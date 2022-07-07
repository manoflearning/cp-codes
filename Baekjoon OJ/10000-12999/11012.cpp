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

const int MAX = 1 << 17;

struct MergeSortTree {
    vt<int> t[MAX << 1];

    void init() {
        FOR(MAX << 1) t[i].clear();
    }

    void build(const vt<pii>& arr) {
        EACH(i, arr) t[i.fr + MAX].push_back(i.sc);

        for (int i = MAX; i < (MAX << 1); i++) sort(all(t[i]));

        for (int i = MAX - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }

    int query(int l, int r, int k1, int k2, int n = 1, int nl = 0, int nr = MAX - 1) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) {
            return upper_bound(all(t[n]), k2) - lower_bound(all(t[n]), k1);
        }

        int mid = (nl + nr) >> 1;
        return query(l, r, k1, k2, n << 1, nl, mid) + query(l, r, k1, k2, n << 1 | 1, mid + 1, nr);
    }
}mstree;

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
        mstree.init();

        int n, m;
        cin >> n >> m;
        vt<pii> arr(n);
        EACH(i, arr) cin >> i.fr >> i.sc;

        mstree.build(arr);

        ll ans = 0;
        FOR(m) {
            int sx, ex, sy, ey;
            cin >> sx >> ex >> sy >> ey;
            ans += mstree.query(sx, ex, sy, ey);
        }

        cout << ans << '\n';
    }

	return 0;
}