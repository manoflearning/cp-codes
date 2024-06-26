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

ll x, y;
vt<ll> arr[4], L, R;

void init() {
    x = y = 0;
    FOR(4) arr[i].clear();
    L.clear();
    R.clear();
}

void modify(ll& ret, ll val) {
    if (abs(val - x) < abs(ret - x) || (abs(ret - x) == abs(val - x) && val < ret)) {
        ret = val;
    }
}

ll cal() {
    ll ret = 1e18;
    EACH(i, L) {
        int idx = lower_bound(all(R), x - i) - R.begin();
        modify(ret, i + R[idx]);
        if (idx > 0) modify(ret, i + R[idx - 1]);
    }
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
    while (tc--) {
        init();

        cin >> x >> y;
        FOR(4 * y) {
            int x; cin >> x;
            arr[i / y].push_back(x);
        }

        FOR(y) FOR(j, y) {
            L.push_back(arr[0][i] + arr[1][j]);
            R.push_back(arr[2][i] + arr[3][j]);
        }

        sort(all(R));
        
        /*EACH(i, L) cout << i << ' ';
        cout << '\n';
        EACH(i, R) cout << i << ' ';
        cout << '\n';*/

        cout << cal() << '\n';
    }

	return 0;
}