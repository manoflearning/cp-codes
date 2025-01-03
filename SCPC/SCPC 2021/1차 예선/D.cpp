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

struct sml {
    ll x1, x2, x3, x4;
};

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	//freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	//freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << '\n';

        int n, m;
        cin >> n >> m;

        vt<sml> e, o;
        FOR(n) {
            int x; cin >> x;

            vt<ll> arr(x);
            EACH(j, arr) cin >> j;
            sort(all(arr));
            
            if (x & 1) o.push_back({ arr[0], arr[1], arr[2], arr[3] });
            else e.push_back({ arr[0], arr[1], arr[2], arr[3] });
        }
        
        if (sz(o) == 2 && sz(e)) {
            ll ans1 = 0, ans2 = 0;
            EACH(i, o) ans1 += 2 * i.x1 + i.x2;
            EACH(i, e) ans1 += 2 * (i.x1 + i.x2) + i.x3 + i.x4;

            EACH(i, o) ans2 += 2 * i.x1 + i.x2 + i.x3 + i.x4;
            EACH(i, e) ans2 += i.x1 + i.x2 + i.x3 + i.x4;

            vt<ll> res;
            res.push_back(max(o[0].x3 + o[0].x4, o[1].x3 + o[1].x4));
            EACH(i, e) res.push_back(i.x3 + i.x4);

            sort(res.rbegin(), res.rend());
            ans2 -= res[0] + res[1];

            cout << min(ans1, ans2) << '\n';
        }
        else {
            ll ans = 0;
            EACH(i, o) ans += 2 * i.x1 + i.x2 + i.x3 + i.x4;
            EACH(i, e) ans += i.x1 + i.x2 + i.x3 + i.x4;
            
            vt<ll> res;
            EACH(i, o) res.push_back(i.x3 + i.x4);
            EACH(i, e) res.push_back(i.x3 + i.x4);

            sort(res.rbegin(), res.rend());
            ans -= res[0] + res[1];

            cout << ans << '\n';
        }
    }

	return 0;
}