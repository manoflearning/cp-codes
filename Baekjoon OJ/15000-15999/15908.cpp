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

int n, a[101010], b[101010];
int dp[101010], psum[101010], ssum[101010];

int isP(int mid) {
    memset(dp, 0, sizeof(dp));
    FOR(i, 1, n + 1) {
        psum[i] = (b[i] <= mid ? 1 : 0) + psum[i - 1];
        ssum[i] = INF;
    }

    dp[n + 1] = 1;
    ssum[n + 1] = n + 1;
    FOR(i, n, 0, -1) {
        if (b[i] <= mid && dp[i + 1]) {
            dp[i] = 1, ssum[i] = i;
        }
        else if (i + a[i] <= n + 1) {
            int idx = ssum[i + a[i]];
            if (psum[idx - 1] - psum[i] >= idx - i - a[i]) {
                dp[i] = 1, ssum[i] = i;
            }
        }

        ssum[i] = min(ssum[i], ssum[i + 1]);
    }

    /*cout << mid << '\n';
    FOR(i, 1, n + 1) cout << dp[i] << ' ';
    cout << '\n';*/

    return dp[1];
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

	cin >> n;
    FOR(n) cin >> a[i + 1];
    FOR(n) cin >> b[i + 1];

    int l = 0, r = 100000;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (isP(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l;

	return 0;
}