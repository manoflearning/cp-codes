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

struct point {
	ll x, y, px, py; // (px, py) is the relative coordinate value at the reference point
	point() : point(0, 0, 0, 0) {}
	point(int sx, int sy) : point(sx, sy, 0, 0) {}
	point(int sx, int sy, int spx, int spy) : x(sx), y(sy), px(spx), py(spy) {}
	bool operator<(const point& rhs) const {
		if (rhs.px * py != px * rhs.py) return rhs.px * py < px * rhs.py;
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
    bool operator<=(const point& rhs) const {
        return rhs.px * py <= px * rhs.py;
    }
};

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

// Does the line segment ab and cd intersect?
bool isCross(point a, point b, point c, point d) {
	ll ab = ccw(a, b, c) * ccw(a, b, d);
	ll cd = ccw(c, d, a) * ccw(c, d, b);
	if (ab == 0 && cd == 0) {
		pii A = { a.x, a.y }, B = { b.x, b.y }, C = { c.x, c.y }, D = { d.x, d.y };
		if (A > B) swap(A, B);
		if (C > D) swap(C, D);
		return (A <= D && C <= B);
	}
	else return (ab <= 0 && cd <= 0);
}

int n;
point st, en;
vt<point> p, ch;

void grahamScan() {
	sort(p.begin(), p.end());

	for (int i = 1; i < sz(p); i++) {
		p[i].px = p[i].x - p[0].x;
		p[i].py = p[i].y - p[0].y;
	}

	sort(p.begin() + 1, p.end());

    vt<int> a;
	a.push_back(0);
	a.push_back(1);
	for (int next = 2; next < sz(p); next++) {
		while (a.size() >= 2) {
			int first = a.back();
			a.pop_back();
			int second = a.back();
			if (ccw(p[second], p[first], p[next]) > 0) {
				a.push_back(first);
				break;
			}
		}
		a.push_back(next);
	}

    EACH(i, a) ch.push_back(p[i]);
}

ll S(const point& a, const point& b, const point& c) {
    ll ret = 0;
    ret += a.x * b.y;
    ret += b.x * c.y;
    ret += c.x * a.y;
    ret -= a.x * c.y;
    ret -= b.x * a.y;
    ret -= c.x * b.y;
    return abs(ret);
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

	cin >> n;
    cin >> st.x >> st.y >> en.x >> en.y;

    p.push_back(st);
    p.push_back(en);
    FOR(n) {
        ll y, xs, xe;
        cin >> y >> xs >> xe;
        if (!isCross(point(xs, y), point(xe, y), st, en)) {
            if (ccw(st, en, point(xs, y)) < 0) p.push_back(point(xe, y));
            else p.push_back(point(xs, y));
        }
    }

    grahamScan();

    ll ans = 0;
    for (int len = 1; len <= sz(ch) / 2; len++) { 
        point stdd;
        int idx;
        stdd.px = ch[0].x - ch[len].x;
        stdd.py = ch[0].y - ch[len].y;

        for (int i = 1; i <= sz(ch); i++) {
            point L, R;
            L.px = ch[i % sz(ch)].x - ch[i - 1].x;
            L.py = ch[i % sz(ch)].y - ch[i - 1].y;
            R.px = ch[(i + 1) % sz(ch)].x - ch[i % sz(ch)].x;
            R.py = ch[(i + 1) % sz(ch)].y - ch[i % sz(ch)].y;

            if (L <= stdd && stdd <= R) { idx = i; break; }
        }
        ans = max(ans, S(ch[0], ch[len], ch[idx]));

        for (int l = 1; l < sz(ch); l++) {
            int r = (l + len) % sz(ch);
            stdd.px = ch[l].x - ch[r].x;
            stdd.py = ch[l].y - ch[r].y;
            while (1) {
                point L, R;
                R.px = ch[(idx + 1) % sz(ch)].x - ch[idx].x;
                R.py = ch[(idx + 1) % sz(ch)].y - ch[idx].y;
                if (stdd <= R) break;
                idx = (idx + 1) % sz(ch);
            }
            ans = max(ans, S(ch[l], ch[r], ch[idx]));
        }
    }

    if (ans & 1) cout << ans / 2 << ".5";
    else cout << ans / 2; 

	return 0;
}