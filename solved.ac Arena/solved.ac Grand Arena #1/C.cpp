//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
ll a[202020];
ll psum[202020];

void init() {

}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void buildPsum() {
    for (int i = 1; i <= n; i++) 
        psum[i] = a[i] + psum[i - 1];
}

const int e = -1e9 - 7;
int flag;  // array size
struct Seg {  // 1-indexed
	vector<int> t, lazy;
	void build(int n) {
        t.clear();
        lazy.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, e);
		lazy.resize(2 * flag, e);
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, int value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] = max(lazy[n], value);
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
		if (r < nl || nr < l) return e;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != e) {
			if (n < flag) {
				lazy[n << 1] = max(lazy[n << 1], lazy[n]);
				lazy[n << 1 | 1] = max(lazy[n << 1 | 1], lazy[n]);
			}
			t[n] = max(t[n], lazy[n]);
			lazy[n] = e;
		}
	}
}dp;

void f() {
    vector<pll> ord;
    ord.push_back({ -1e18, 0 });
    for (int i = 1; i <= n; i++) 
        ord.push_back({ psum[i], i });
    sort(all(ord));

    vector<int> idx(n + 1);
    for (int i = 0; i < sz(ord); i++) {
        if (ord[i].sc >= 1) idx[ord[i].sc] = i;
    }

    dp.build(n);

    for (int i = 1; i <= n; i++) {
        dp.modify(idx[i], idx[i], (psum[i] > 0 ? 1 : (psum[i] < 0 ? -1 : 0)));
    }
    for (int i = 1; i < n; i++) {
        int val = dp.query(idx[i], idx[i]);
        int lb = -1, ub = -1;
        // cout << i << ' ' << val << '\n';
        // psum[j] is smaller than psum[i]
        lb = 1;
        ub = lower_bound(all(ord), make_pair(psum[i], -1ll)) - ord.begin() - 1;
        dp.modify(lb, ub, -1 + val);
        // cout << lb << ' ' << ub << ", ";
        // psum[j] is equals to psum[i]
        lb = lower_bound(all(ord), make_pair(psum[i], -1ll)) - ord.begin();
        ub = lower_bound(all(ord), make_pair(psum[i] + 1, -1ll)) - ord.begin() - 1;
        dp.modify(lb, ub, val);
        // cout << lb << ' ' << ub << ", ";
        // psum[j] is bigger than psum[i]
        lb = lower_bound(all(ord), make_pair(psum[i] + 1, -1ll)) - ord.begin();
        ub = n;
        dp.modify(lb, ub, 1 + val);
        // cout << lb << ' ' << ub << '\n';
    }

    cout << (dp.query(idx[n], idx[n]) > 0 ? "YES\n" : "NO\n");
}

// void naive() { // O(n^2)
//     vector<int> dp(n + 1, -INF);
//     dp[0] = 0;
//     for (int i = 1; i <= n; i++) {
//         dp[i] = -INF;
//         for (int j = 1; j <= i; j++) {
//             ll sum = psum[i] - psum[j - 1];
//             if (sum > 0) dp[i] = max(dp[i], 1 + dp[j - 1]);
//             if (sum < 0) dp[i] = max(dp[i], -1 + dp[j - 1]);
//             if (sum == 0) dp[i] = max(dp[i], dp[j]);
//         }
//     }

//     cout << (dp[n] > 0 ? "YES\n" : "NO\n");
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        buildPsum();

        f();
    }
}