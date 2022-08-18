#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

int n;
vt<int> a, cc, arr[303030];
int dp[303030];

void init() {
    FOR(n) dp[i] = -1;
    FOR(sz(cc)) arr[i].clear();
    cc.clear();
}

void coco() {
    EACH(i, a) {
        cc.push_back(i);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
}

int f(int idx) {
    int& ret = dp[idx];
    if (ret != -1) return ret;

    ret = 1;

    int lb = lower_bound(all(cc), a[idx] - n - idx) - cc.begin();
    int rb = upper_bound(all(cc), a[idx] + n + idx) - cc.begin();

    FOR(k, lb, min(sz(cc), 2 * rb)) {
        int st = upper_bound(all(arr[k]), idx) - arr[k].begin();
        FOR(j, st, sz(arr[k])) {
            int i = arr[k][j];
            if (i - a[idx] >= (a[i] ^ idx)) break;
            if ((a[idx] ^ i) < (a[i] ^ idx)) {
                ret = max(ret, f(i) + 1);
            }
        }
    }

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    FOR(303030) dp[i] = -1;

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		cin >> n;

        a.resize(n);
        FOR(i, n) cin >> a[i];

        coco();

        FOR(i, n) {
            int idx = lower_bound(all(cc), a[i]) - cc.begin();
            arr[idx].push_back(i);
        }

        int ans = 0;
        FOR(i, n)
            ans = max(ans, f(i));

        cout << ans << '\n';

        init();
	}

	return 0;
}