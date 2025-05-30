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

struct point {
    ll x, y, dx, dy;
    bool operator<(const point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

ll n, t;
vector<point> a, p, ch;

void input() {
    cin >> n >> t;
    a.resize(n);
    p.resize(n);
    ch.resize(n);
    for (auto& i : a) cin >> i.x >> i.y >> i.dx >> i.dy;
}

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

ll cccw(point a, point b, point c, point d) {
    d.x -= c.x - b.x;
    d.y -= c.y - b.y;
    return ccw(a, b, d);
}

ll dist(const point& p1, const point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool cmp(const point& p1, const point& p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}

ll rotatingCallipers() {
    sort(p.begin(), p.end());
    sort(p.begin() + 1, p.end(), cmp);

    ch[0] = p[0];
    ch[1] = p[1];

    ll fl = 2, cnt = 2;
    for (int i = 2; i < n; i++) {
        while (fl >= 2 && ccw(ch[fl - 2], ch[fl - 1], p[i]) <= 0) fl--;
        ch[fl] = p[i], fl++;
    }

    ll fl2 = 1, ret = 0;
    for (int i = 0; i < fl; i++) {
        while ((fl2 + 1) != i && cccw(ch[i], ch[i + 1], ch[fl2 % fl], ch[(fl2 + 1) % fl]) > 0) {
            if (ret < dist(ch[i], ch[fl2 % fl])) {
                ret = dist(ch[i], ch[fl2 % fl]);
            }
            fl2++;
        }
        if (ret < dist(ch[i], ch[fl2 % fl])) {
            ret = dist(ch[i], ch[fl2 % fl]);
        }
    }
    return ret;
}

ll cal(ll idx) {
    FOR(sz(a)) {
        p[i].x = a[i].x + idx * a[i].dx;
        p[i].y = a[i].y + idx * a[i].dy;
    }
    return rotatingCallipers();
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

	input();

    int l = 0, r = t;
    while (r - l > 3) {
        ll mid1 = (2 * l + r) / 3;
        ll mid2 = (l + 2 * r) / 3;

        ll x1 = cal(mid1), x2 = cal(mid2);
        if (x1 <= x2) r = mid2;
        else l = mid1 + 1;
    }

    ll ans1 = -1, ans2 = LLONG_MAX;
    FOR(i, l, r + 1) {
        ll res = cal(i);
        if (ans2 > res) {
            ans1 = i, ans2 = res;
        }
    }

    cout << ans1 << '\n' << ans2;

	return 0;
}