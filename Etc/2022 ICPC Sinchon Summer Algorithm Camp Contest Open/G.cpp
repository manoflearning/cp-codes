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

ll n, k;
ll x[202020], y[202020], z[202020];
ll ans[202020];
ll mnxy[202020];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	FOR(202020) {
        ans[i] = INF;
        mnxy[i] = INF;
    }
    
    cin >> n >> k;
    FOR(i, 1, n + 1) {
        cin >> x[i] >> y[i] >> z[i];
    }

    FOR(i, 1, n + 1) {
        ans[i] = min(ans[i], abs(x[1] - x[i]));
        ans[i] = min(ans[i], abs(y[1] - y[i]));
        mnxy[z[i] % k] = min(mnxy[z[i] % k], ans[i] + z[i]);
    }

    FOR(i, 2, n + 1) {
        ans[i] = min(ans[i], z[i] + mnxy[k - z[i] % k]);
    }

    FOR(i, 1, n + 1) {
        cout << ans[i] << '\n';
    }

	return 0;
}