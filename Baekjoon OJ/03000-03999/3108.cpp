//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 1010101;

vector<int> uf(MAX, -1);

int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	uf[A] += uf[B];
	uf[B] = A;
}

struct Point {
    ll x, y;
};

struct Line {
    Point p1, p2;
};

struct Rec {
    Line a, b, c, d;
};

int n;
vector<Rec> a;

ll ccw(const Point& a, const Point& b, const Point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

// Does the line segment ab and cd intersect?
bool isCross(Point a, Point b, Point c, Point d) {
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

bool isCross(Line a, Line b) {
    return isCross(a.p1, a.p2, b.p1, b.p2);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    a.resize(n + 1);

    int bit = 0;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if ((!x1 || !x2) && (y1 <= 0 && 0 <= y2)) bit = 1;
        if ((!y1 || !y2) && (x1 <= 0 && 0 <= x2)) bit = 1;
        a[i].a = { { x1, y1 }, { x1, y2 }};
        a[i].b = { { x1, y1 }, { x2, y1 }};
        a[i].c = { { x2, y1 }, { x2, y2 }};
        a[i].d = { { x1, y2 }, { x2, y2 }};
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (isCross(a[i].a, a[j].a)) merge(i, j);
            if (isCross(a[i].a, a[j].b)) merge(i, j);
            if (isCross(a[i].a, a[j].c)) merge(i, j);
            if (isCross(a[i].a, a[j].d)) merge(i, j);

            if (isCross(a[i].b, a[j].a)) merge(i, j);
            if (isCross(a[i].b, a[j].b)) merge(i, j);
            if (isCross(a[i].b, a[j].c)) merge(i, j);
            if (isCross(a[i].b, a[j].d)) merge(i, j);

            if (isCross(a[i].c, a[j].a)) merge(i, j);
            if (isCross(a[i].c, a[j].b)) merge(i, j);
            if (isCross(a[i].c, a[j].c)) merge(i, j);
            if (isCross(a[i].c, a[j].d)) merge(i, j);

            if (isCross(a[i].d, a[j].a)) merge(i, j);
            if (isCross(a[i].d, a[j].b)) merge(i, j);
            if (isCross(a[i].d, a[j].c)) merge(i, j);
            if (isCross(a[i].d, a[j].d)) merge(i, j);
        }
    }

    set<int> s;
    for (int i = 1; i <= n; i++)
        s.insert(find(i));

    cout << sz(s) - bit;

	return 0;
}