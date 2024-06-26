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

struct naemo {
    int sx, sy, ex, ey;
};

int n;
vt<naemo> a;
vt<ll> ccx, ccy;

void init() {
    a.clear();
    ccx.clear();
    ccy.clear();
}

void input() {
    cin >> n;
    a.resize(n);
    EACH(i, a) {
        cin >> i.sx >> i.sy;
        cin >> i.ex >> i.ey;
    }
}

void ccom() {
    EACH(i, a) {
        ccx.push_back(i.sx);
        ccx.push_back(i.ex);
        ccy.push_back(i.sy);
        ccy.push_back(i.ey);
    }

    sort(all(ccx));
    sort(all(ccy));
    ccx.erase(unique(all(ccx)), ccx.end());
    ccy.erase(unique(all(ccy)), ccy.end());

    EACH(i, a) {
        i.sx = lower_bound(all(ccx), i.sx) - ccx.begin();
        i.ex = lower_bound(all(ccx), i.ex) - ccx.begin();
        i.sy = lower_bound(all(ccy), i.sy) - ccy.begin();
        i.ey = lower_bound(all(ccy), i.ey) - ccy.begin();
    }
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

        input();

        ccom();

        ll ans = 0;
        FOR(i, sz(ccx)) {
            vt<int> psum(sz(ccy));
            EACH(j, a) {
                if (j.sx <= i && i < j.ex) {
                    psum[j.sy]++;
                    psum[j.ey]--;
                }
            }

            FOR(j, sz(ccy)) {
                if (j > 0) psum[j] += psum[j - 1];
                if (psum[j]) ans += (ccy[j + 1] - ccy[j]) * (ccx[i + 1] - ccx[i]);
            }
        }

        cout << ans << '\n';
	}

	return 0;
}