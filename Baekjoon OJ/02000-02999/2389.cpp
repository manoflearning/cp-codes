#include <bits/stdc++.h>
using namespace std;

struct Point { long double x, y; };
struct Circle { Point c; long double r; };

int n;
vector<Point> p;

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

int isValidCircle(const Circle& ci) {
    for (auto& i : p) {
        if (ci.r + 1e-9 < dist(i, ci.c)) return 0;
    }
    return 1;
}

Circle minimumEnclosingCircle() {
    if (n == 1) return { p[0], 0.0 };

    Circle ret = { { 0, 0 }, 1e18 };

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Circle res = circleFrom(p[i], p[j]);
            
            if (res.r < ret.r && isValidCircle(res)) ret = res;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                Circle res = circleFrom(p[i], p[j], p[k]);
                
                if (res.r < ret.r && isValidCircle(res)) ret = res;
            }
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    p.resize(n);
    for (auto& i : p)
        cin >> i.x >> i.y;
    
    Circle ans = minimumEnclosingCircle();

    cout << fixed;
    cout.precision(11);
    cout << ans.c.x << ' ' << ans.c.y << ' ' << ans.r;
}