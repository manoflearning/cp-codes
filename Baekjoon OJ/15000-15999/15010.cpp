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
	ll x, y;
};

struct lineSeg {
    point s, e;
};

int n, cCnt, eCnt, vi[1010];
vt<lineSeg> a;
vt<int> adj[1010];

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

void dfs(int v) {
    vi[v] = 1;
    EACH(i, adj[v]) {
        if (!vi[i]) dfs(i);
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

	cin >> n;
    a.resize(n);
    EACH(i, a) cin >> i.s.x >> i.s.y >> i.e.x >> i.e.y;

    FOR(n) {
        FOR(j, i + 1, n) {
            if (isCross(a[i].s, a[i].e, a[j].s, a[j].e)) {
                adj[i + 1].push_back(j + 1);
                adj[j + 1].push_back(i + 1);
                eCnt++;
            }
        }
    }

    FOR(i, 1, n + 1) {
        if (!vi[i]) { dfs(i); cCnt++; }
    }

    cout << cCnt - n + eCnt;

	return 0;
}