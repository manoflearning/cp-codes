#include <bits/stdc++.h>
using namespace std;

struct Point { long double x, y; };
struct Circle { Point c; long double r; };

long double dist(const Point& a, const Point& b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

Point getCircleCenter(const Point& a, const Point& b) {
    long double A = a.x * a.x + a.y * a.y;
    long double B = b.x * b.x + b.y * b.y;
    long double C = a.x * b.y - a.y * b.x;
    return { (b.y * A - a.y * B) / (2 * C), (a.x * B - b.x * A) / (2 * C) };
}
Circle circleFrom(const Point& a, const Point& b, const Point& c) {
    Point i = getCircleCenter({ b.x - a.x, b.y - a.y }, { c.x - a.x, c.y - a.y });
    i.x += a.x;
    i.y += a.y;
    return { i, dist(a, i) };
}
Circle circleFrom(const Point& a, const Point& b) {
    Point c = { (a.x + b.x) / 2.0, (a.y + b.y) / 2.0 };
    return { c, dist(a, b) / 2.0 };
}

int isValidCircle(const Circle& ci, vector<Point>& p) {
    for (auto& i : p) {
        if (ci.r + 1e-9 < dist(i, ci.c)) return 0;
    }
    return 1;
}

Circle minimumEnclosingCircle(int n, const vector<Point>& p) {
    Circle ret = { { 0, 0 }, 0 };
    for (int i = 0; i < n; i++) {
        if (dist(ret.c, p[i]) <= ret.r) continue;
        ret.c = p[i], ret.r = 0;
        for (int j = 0; j < i; j++) {
            if (dist(ret.c, p[j]) <= ret.r) continue;
            ret = circleFrom(p[i], p[j]);
            for (int k = 0; k < j; k++) {
                if (dist(ret.c, p[k]) <= ret.r) continue;
                ret = circleFrom(p[i], p[j], p[k]);
            }
        }
    }
    return ret;
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<Point> p(n);
    for (auto& i : p)
        cin >> i.x >> i.y;
    
    random_shuffle(p.begin(), p.end());

    Circle ans = minimumEnclosingCircle(n, p);

    cout << fixed;
    cout.precision(11);
    cout << ans.c.x << ' ' << ans.c.y << '\n' << ans.r;
}