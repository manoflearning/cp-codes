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
ll a[101010], pxor[101010], dp[101010];
map<ll, int> mp;

/*ll query(int l, int r) {
    return pxor[r] ^ pxor[l - 1];
}

ll f(int idx) {
    ll& ret = dp[idx];
    if (ret != -1) return ret;
    if (idx == n + 1) return ret = 0;
    if (a[idx] == 0) return ret = f(idx + 1);

    ret = f(idx + 1) + 1;
    FOR(i, idx + 1, n + 1) {
        if (a[i] == query(idx, i - 1)) {
            ret = min(ret, f(i + 1) + i - idx);
        }
    }
    return ret;
}*/

void init() {
    mp.clear();
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
		cin >> n;
        
        FOR(i, 1, n + 1) cin >> a[i];

        FOR(i, 1, n + 1)
            pxor[i] = a[i] ^ pxor[i - 1];

        dp[n + 1] = 0;
        FOR(i, n, 0, -1) {
            if (!a[i]) {
                dp[i] = dp[i + 1];
                continue;
            }

            dp[i] = dp[i + 1] + 1;
            auto it = mp.find(pxor[i - 1]);
            if (it != mp.end()) {
                dp[i] = min(dp[i], dp[it->sc + 1] + it->sc - i);
            }
            //cout << i << ' ' << dp[i] << '\n';
            it = mp.find(a[i] ^ pxor[i - 1]);
            if (it != mp.end()) it->sc = i;
            else mp.insert({ a[i] ^ pxor[i - 1], i });
        }

        cout << dp[1] << '\n';

        init();
	}

	return 0;
}