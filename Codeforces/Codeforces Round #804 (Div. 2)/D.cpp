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

int n, del[5050][5050], dp[5050];
vt<int> a;

void input() {
    cin >> n;
    a.resize(n);
    EACH(i, a) cin >> i;
}

void buildDel() {
    FOR(n) {
        vt<int> cnt(n + 1);
        int mx = 0;
        FOR(j, i, n) {
            cnt[a[j]]++;
            mx = max(mx, cnt[a[j]]);
            if (mx <= (j - i + 1) / 2 && (j - i + 1) % 2 == 0) {
                del[i][j] = 1;
            }
        }
    }
}

void init() {
    FOR(n) FOR(j, i, n) del[i][j] = 0;
    FOR(n) dp[i] = 0;
    a.clear();
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

    FOR(5050) {
        FOR(j, i - 1, -1, -1) {
            del[i][j] = 1;
        }
    }

	int tc; cin >> tc;
    while (tc--) {
        input();

        buildDel();

        dp[0] = 1;
        FOR(i, 1, n) {
            //if (a[i - 1] == a[i] && dp[i - 1] > 0) dp[i] = max(dp[i], dp[i - 1] + 1);
            if (del[0][i - 1]) dp[i] = max(dp[i], 1);
            FOR(j, i) {
                if (del[j + 1][i - 1] && a[j] == a[i] && dp[j] > 0) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            //cout << i << ' ' << dp[i] << '\n';
        }

        int ans = 0;
        FOR(i, n) {
            if (del[i + 1][n - 1]) {
                ans = max(ans, dp[i]);
            }
        }

        cout << ans << '\n';

        init();
    }

	return 0;
}