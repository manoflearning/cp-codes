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
const ll INF = 1e18 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
vt<pll> a;

ll cal(int bit) {
    int cnt = 0;
    FOR(n) if (bit & (1 << i)) cnt++;
    if (cnt != n / 2) return INF;
    pll ret = { 0, 0 };
    FOR(n) {
        if (bit & (1 << i)) ret.fr += a[i].fr, ret.sc += a[i].sc;
        else ret.fr -= a[i].fr, ret.sc -= a[i].sc;
    }
    return ret.fr * ret.fr + ret.sc * ret.sc;
}

ll bt(int bit, int idx) {
    if (idx == n) return cal(bit);

    ll ret = INF;
    ret = min(ret, bt(bit, idx + 1));
    ret = min(ret, bt(bit | (1 << idx), idx + 1));

    return ret;
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

    cout << fixed;
    cout.precision(8);
    while (tc--) {
        cin >> n;
        a.resize(n);
        EACH(i, a) cin >> i.fr >> i.sc;

        cout << sqrt(bt(0, 0)) << '\n';
    }

	return 0;
}