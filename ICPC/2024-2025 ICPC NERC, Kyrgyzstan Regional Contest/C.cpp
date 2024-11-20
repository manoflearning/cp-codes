#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e9 + 7;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int n;
struct Point {
  ll x, y;
  bool operator<(const Point &rhs) const {
    return x ^ rhs.x ? x < rhs.x : y < rhs.y;
  }
  bool operator==(const Point &rhs) const {
    return tuple<ll, ll>(x, y) == tuple<ll, ll>(rhs.x, rhs.y);
  }
  bool operator!=(const Point &rhs) const {
    return tuple<ll, ll>(x, y) != tuple<ll, ll>(rhs.x, rhs.y);
  }
};
vector<Point> p;
vector<Point> s;

const Point o = {0, 0};
ll ccw(const Point &a, const Point &b, const Point &c) {
  // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
  ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
inline ll dist(const Point &v) { return v.x * v.x + v.y * v.y; }
// If the angle between any two points and the origin is less than 180 degrees,
// they can be sorted through the cross product of the vectors.
// Therefore, the points were divided into 1st and 4th quadrants and 2nd and 3rd quadrants,
// and the points in the 1st and 4th quadrants were arranged in front.
void sortByAngular() {
  sort(s.begin(), s.end(), [&](const Point &lhs, const Point &rhs) {
    if ((lhs < o) ^ (rhs < o)) return (lhs < o) < (rhs < o);
    if (ccw(o, lhs, rhs)) return ccw(o, lhs, rhs) > 0;
    return dist(lhs) < dist(rhs);
  });
}

bool islte90(const Point &a, const Point &b) {
    ll ret = a.x * b.x + a.y * b.y;
    return ret >= 0 ? 1 : 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;

    s.resize(n - 1);
    for (int i = 0; i + 1 < n; i++) {
        if (p[i] == p[i + 1]) {
            cout << "NO\n";
            exit(0);
        }

        s[i] = {p[i + 1].x - p[i].x, p[i + 1].y - p[i].y};
        ll g = gcd(abs(s[i].x), abs(s[i].y));
        s[i].x /= g, s[i].y /= g;
    }

    sortByAngular();

    s.erase(unique(all(s)), s.end());

    if (sz(s) == 0) {
        cout << "YES\n";
        cout << 1 << ' ' << 0 << '\n';
        cout << 0 << ' ' << 1 << '\n';
    } else if (sz(s) == 1) {
        cout << "YES\n";
        Point ans2 = s[0];
        Point ans1 = {ans2.y, -ans2.x};
        cout << ans1.x << ' ' << ans1.y << '\n';
        cout << ans2.x << ' ' << ans2.y << '\n';
    } else if (ccw(o, s[0], s[sz(s) - 1]) > 0) {
        Point ans2 = s[sz(s) - 1];
        Point ans1 = {ans2.y, -ans2.x};
        cout << "YES\n";
        cout << ans1.x << ' ' << ans1.y << '\n';
        cout << ans2.x << ' ' << ans2.y << '\n';
    } else {
        Point p1 = {INF, INF}, p2 = {INF, INF};
        for (auto i : s) {
            if (i.x > 0) p1 = i;
            if (i.x < 0 && p2.x == INF) p2 = i;
            if (i.x == 0 && i.y > 0) {
                cout << "NO\n";
                exit(0);
            }
        }

        if (p1.x == INF || p2.x == INF) {
            cout << "NO\n";
            exit(0);
        }

        if (ccw(o, p2, p1) > 0) {
            Point ans2 = p1;
            Point ans1 = {ans2.y, -ans2.x};
            cout << "YES\n";
            cout << ans1.x << ' ' << ans1.y << '\n';
            cout << ans2.x << ' ' << ans2.y << '\n';
        } else {
            cout << "NO\n";
            exit(0);
        }
    }
}
