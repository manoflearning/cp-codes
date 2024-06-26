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

ll R;
vt<vt<int>> a, b;
int cnt1, cnt2;

void draw_circle_perimeter(ll r) {
    for (ll x = -r; x <= r; x++) {
        ll y = (ll)(sqrt(r * r - x * x) + 0.5);
        
        if (!a[y + R][x + R]) a[y + R][x + R] = 1, cnt2++;
        if (!a[-y + R][x + R]) a[-y + R][x + R] = 1, cnt2++;
        if (!a[x + R][y + R]) a[x + R][y + R] = 1, cnt2++;
        if (!a[x + R][-y + R]) a[x + R][-y + R] = 1, cnt2++;
    }
}

void draw_circle_filled_wrong() {
    for (ll i = 0; i <= R; i++) {
        draw_circle_perimeter(i);
    }
}

void draw_circle_filled() {
    for (ll x = -R; x <= R; x++) {
        for (ll y = -R; y <= R; y++) {
            if ((ll)(sqrt(x * x + y * y) + 0.5) <= R) {
                if (!b[y + R][x + R]) b[y + R][x + R] = 1, cnt1++;
            }
        }
    }
}

void init() {
    a.clear();
    b.clear();
    cnt1 = cnt2 = 0;
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

    FOR(t, 1, tc + 1) {
        cout << "Case #" << t << ": ";

        cin >> R;

        a.resize(2 * R + 1, vt<int>(2 * R + 1));
        b.resize(2 * R + 1, vt<int>(2 * R + 1));

        draw_circle_filled();

        draw_circle_filled_wrong();

        //cout << cnt1 << ' ' << cnt2 << '\n';
        cout << (ll)fabs(cnt1 - cnt2) << '\n';

        init();
    }

	return 0;
}