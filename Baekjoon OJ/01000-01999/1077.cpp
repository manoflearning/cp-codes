#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define pdd pair<ld, ld>

struct point {
    ld x, y;
};

int n, m;
vector<point> p, q, ch;

void input() {
    cin >> n >> m;
    p.resize(n);
    q.resize(m);
    for (auto& i : p)
        cin >> i.x >> i.y;
    for (auto& i : q)
        cin >> i.x >> i.y;
}

int ccw(const point& a, const point& b, const point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ld res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

// Does the line segment ab and cd intersect?
bool isCross(point a, point b, point c, point d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        pdd A = { a.x, a.y }, B = { b.x, b.y }, C = { c.x, c.y }, D = { d.x, d.y };
        if (A > B) swap(A, B);
        if (C > D) swap(C, D);
        return (A <= D && C <= B);
    }
    else return (ab <= 0 && cd <= 0);
}

point getIntersectionPoint(point a, point b, point c, point d) {
    ld under = (d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y);
    
    ld _t = (d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x);
    ld _s = (b.x - a.x) * (a.y - c.y) - (b.y - a.y) * (a.x - c.x);

    ld t = _t / under;
    ld s = _s / under;

    return { a.x + t * (b.x - a.x), a.y + t * (b.y - a.y) };
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (isCross(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m])) {
                point res = getIntersectionPoint(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]);
                ch.push_back(res);
            }
        }
    }

    return 0;
}