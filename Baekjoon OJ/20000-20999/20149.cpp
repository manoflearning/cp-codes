#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

struct Point {
    ll x, y;
    bool operator<(const Point& rhs) const {
        return (x ^ rhs.x ? x < rhs.x : y < rhs.y);
    }
    bool operator>(const Point& rhs) const {
        return (x ^ rhs.x ? x > rhs.x : y > rhs.y);
    }
    bool operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    Point operator-(const Point& rhs) const {
        return { x - rhs.x, y - rhs.y };
    }
    ll operator*(const Point& rhs) const { // cross product
        return x * rhs.y - y * rhs.x;
    }
};

ll ccw(const Point& a, const Point& b, const Point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

// Does the line segment ab and cd intersect?
bool isCross(const Point& a, const Point& b, const Point& c, const Point& d) {
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

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

pll getSlope(const Point& a, const Point& b) {
    pll slope = { b.y - a.y, b.x - a.x };
    if (slope.sc < 0 || (slope.sc == 0 && slope.fr < 0)) {
        slope.fr *= -1, slope.sc *= -1;
    }
    ll g = gcd(abs(slope.fr), abs(slope.sc));
    slope.fr /= g, slope.sc /= g;
    return slope;
}

// Get intersection point of two line segments ab and cd.
// Note: ab, cd is not a infinite line, it's a line segment.
void getIntersectionPoint(Point a, Point b, Point c, Point d) {
    if (isCross(a, b, c, d)) {
        cout << 1 << '\n';

        if (getSlope(a, b) == getSlope(c, d)) {
            if (a > b) swap(a, b); // wlog a <= b
            if (c > d) swap(c, d); // wlog c <= d
            if (b == c || a == d) {
                if (b == c) cout << b.x << ' ' << b.y;
                if (a == d) cout << a.x << ' ' << a.y;
            }
        }
        else {
            b = b - a;
            d = d - c;
            double p = (double)((c - a) * d) / (b * d);
            
            // res = a + p * b
            pair<double, double> res = { a.x + p * b.x, a.y + p * b.y };
            cout << res.fr << ' ' << res.sc;
        }
    }
    else cout << 0 << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    Point p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    cin >> p3.x >> p3.y >> p4.x >> p4.y;

    cout << fixed;
    cout.precision(10);
    getIntersectionPoint(p1, p2, p3, p4);
}