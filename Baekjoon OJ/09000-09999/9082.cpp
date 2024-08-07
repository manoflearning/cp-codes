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

int n, dp[101][4];
string s;
vt<int> a;

void init() {
    FOR(101) FOR(j, 4) dp[i][j] = -1;
}

int f(int idx, int bit) {
    int& ret = dp[idx][bit];
    if (ret != -1) return ret;
    if (idx == n) return ret = 0;

    int cnt = (bit & 1) + ((bit & 2) ? 1 : 0);
    
    if (s[idx] == '*') {
        if (a[idx - 1] < cnt + 1) return ret = 0;
        else if (a[idx - 1] == cnt + 1) return ret = f(idx + 1, bit / 2 + 2) + 1;
        else if (a[idx - 1] >= cnt + 2) return ret = 0;
    }

    if (a[idx - 1] < cnt) return ret = 0;
    else if (a[idx - 1] == cnt) return ret = f(idx + 1, bit / 2);
    else if (a[idx - 1] == cnt + 1) return ret = f(idx + 1, bit / 2 + 2) + 1;
    else if (a[idx - 1] >= cnt + 2) return ret = 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
        init();

		cin >> n;
        cin >> s;
        a.resize(n);
        FOR(n) a[i] = s[i] - '0';
        cin >> s;

        int ans = 0;
        FOR(4) {
            int cnt = (i & 1) + ((i & 2) ? 1 : 0);
            if (cnt == a[0] && cnt <= a[1]) {
                ans = max(ans, f(2, i) + cnt);
            }
        }
        cout << ans << '\n';
	}

	return 0;
}