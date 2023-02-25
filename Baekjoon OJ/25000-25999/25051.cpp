#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Point {
    ll x, y, w;
    bool operator<(const Point& rhs) const {
        return x ^ rhs.x ? x < rhs.x : y < rhs.y;
    }
};

const Point o = { 0, 0 };

int n, m;
vector<Point> p;

void input() {
    cin >> n >> m;
    p.resize(n);
    for (auto& i : p)
        cin >> i.x >> i.y >> i.w;
}

ll ccw(const Point& a, const Point& b, const Point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

inline ll dist(const Point& v) { return v.x * v.x + v.y * v.y; }

ll ans = -1e18;
void solve() {
    for (int i = 0; i < m; i++) {
        ll len; cin >> len;

        // two pointer
        ll res = -len;
        int r = 0;
        for (int l = 0; l < n; l++) {
            Point q = { -p[l].y, p[l].x };
            while (r < min(2 * n, l + n) && ccw(o, p[l], p[r % n]) >= 0 && ccw(o, q, p[r % n]) <= 0) {
                res += (dist(p[r % n]) <= len ? p[r % n].w : 0);
                r++;
            }
            ans = max(ans, res);
            res -= (dist(p[l]) <= len ? p[l].w : 0);
        }
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

    // sort by angular
    sort(p.begin(), p.end(), [&](const Point& lhs, const Point& rhs) {
        return (lhs < o) ^ (rhs < o) ? (lhs < o) < (rhs < o) : ccw(o, lhs, rhs) > 0;
    });

    solve();

    cout << ans;
}