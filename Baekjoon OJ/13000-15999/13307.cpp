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
    int isB, idx;
	point() : point(0, 0, 0, 0, 0, 0) {}
	point(int sx, int sy, int sisB, int sidx) : point(sx, sy, 0, 0, sisB, sidx) {}
	point(int sx, int sy, int spx, int spy, int sisB, int sidx) : x(sx), y(sy), px(spx), py(spy), isB(sisB), idx(sidx) {}
	bool operator<(const point& rhs) const {
		if (rhs.px * py != px * rhs.py) return rhs.px * py < px * rhs.py;
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
    bool operator!=(const point& rhs) const {
        return isB != rhs.isB || idx != rhs.idx;
    }
};

int N;
vt<point> p;
pll ans[1010];

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back(point(x, y, 1, i + 1));
	}
    for (int i = 0; i < 2 * N; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back(point(x, y, 0, i + 1));
	}
}

int getBlInCH(vt<point>& a) {
	sort(a.begin(), a.end());

	for (int i = 1; i < sz(a); i++) {
		a[i].px = a[i].x - a[0].x;
		a[i].py = a[i].y - a[0].y;
	}

	sort(a.begin() + 1, a.end());

    vt<int> st;
	st.push_back(0);
	st.push_back(1);
	for (int next = 2; next < sz(a); next++) {
		while (st.size() >= 2) {
			int first = st.back();
			st.pop_back();
			int second = st.back();
			if (ccw(p[second], p[first], p[next]) > 0) {
				st.push_back(first);
				break;
			}
		}
		st.push_back(next);
	}

    vt<point> tmp;
    int ret = 0;
    EACH(i, st) {
        if (a[i].isB) { tmp.push_back(a[i]); ret = 1; break; }
    }
    if (tmp.empty()) tmp.push_back(a[st[0]]);

    EACH(i, a) if (i != tmp[0]) tmp.push_back(i);
    EACH(i, tmp) i.px = i.py = 0;
    a = tmp;
    
    return ret;
}

int isValid(const vt<point>& a) {
    int ret = 0;
    EACH(i, a) {
        if (i.isB) ret += 2;
        else ret -= 1;
    }
    return ret == 0;
}

void dc(vt<point> a) {
    if (a.empty()) return;
    assert(isValid(a));

    int isBlChSt = getBlInCH(a);

    for (int i = 1; i < sz(a); i++) {
		a[i].px = a[i].x - a[0].x;
		a[i].py = a[i].y - a[0].y;
	}

    sort(a.begin() + 1, a.end());
    
    /*cout << a[0].x << ' ' << a[0].y << ' ' << a[0].idx << '\n';
    for (int i = 1; i < sz(a); i++)
        cout << a[i].x << ' ' << a[i].y << ' ' << a[i].idx << '\n';
    cout << '\n';**/
    if (isBlChSt) {
        int res = 0, idx1 = -1, idx2 = -1;
        for (int i = 1; i < sz(a); i++) {
            if (a[i].isB) res += 2;
            else res -= 1;

            if (res == -1 && idx1 == -1) idx1 = i;
            if (res == -2 && idx2 == -1) idx2 = i;
        }

        ans[a[0].idx] = { a[idx1].idx, a[idx2].idx };

        vt<point> b, c, d;
        for (int i = 1; i < idx1; i++) 
            b.push_back(point(a[i].x, a[i].y, a[i].isB, a[i].idx));
        for (int i = idx1 + 1; i < idx2; i++)
            c.push_back(point(a[i].x, a[i].y, a[i].isB, a[i].idx));
        for (int i = idx2 + 1; i < sz(a); i++)
            d.push_back(point(a[i].x, a[i].y, a[i].isB, a[i].idx));

        dc(b); dc(c); dc(d);
        /*if (sz(b)) dc(b);
        if (sz(c)) dc(c);
        if (sz(d)) dc(d);*/
    }
    else {
        int res = -1, idx = -1;
        for (int i = 1; i < sz(a); i++) {
            if (a[i].isB) res += 2;
            else res -= 1;

            if (res == 0) { idx = i; break; } 
        }
        
        /*if (idx == sz(a) - 1) {
            res = 0;
            reverse(all(a));
            for (int i = 0; i < sz(a); i++) {
                if (a[i].isB) res += 2;
                else res -= 1;

                if (res == 0) { idx = i; break; } 
            }
        }*/

        vt<point> b, c;
        for (int i = 0; i <= idx; i++) 
            b.push_back(point(a[i].x, a[i].y, a[i].isB, a[i].idx));
        for (int i = idx + 1; i < sz(a); i++) 
            c.push_back(point(a[i].x, a[i].y, a[i].isB, a[i].idx));

        dc(b); dc(c);
        /*if (sz(b)) dc(b);
        if (sz(c)) dc(c);*/
    }
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

    dc(p);

    FOR(i, 1, N + 1)
        cout << ans[i].fr << ' ' << ans[i].sc << '\n';

	return 0;
}