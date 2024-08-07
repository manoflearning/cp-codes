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
	ll x, y;
	bool operator<(const point& rhs) const {
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
};

int n, m;
vector<point> a, b;
vector<point> p, ans;
vector<int> st;

void input() {
    cin >> n >> m;
    
    a.resize(n);
    b.resize(m);
    EACH(i, a) cin >> i.x >> i.y;
    EACH(i, b) cin >> i.x >> i.y;

    EACH(i, a) {
        EACH(j, b) {
            p.push_back({ i.x + j.x, i.y + j.y });
        }
    }
}

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

ll dist(const point& p1, const point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool cmp(const point& p1, const point& p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}

void grahamScan() {
	sort(p.begin(), p.end());

	sort(p.begin() + 1, p.end(), cmp);

	st.push_back(0);
	st.push_back(1);
	for (int next = 2; next < sz(p); next++) {
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
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    grahamScan();

    cout << sz(st) << '\n';
    EACH(i, st)
        cout << p[i].x << ' ' << p[i].y << '\n';

	return 0;
}