#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Point {
    ll x, y;
    bool operator<(const Point& rhs) const {
        if (y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
};

int n;
vector<Point> p;
vector<int> st;

void init() {
    p.clear();
    st.clear();
}

void input() {
    cin >> n;
    if (n == 0) exit(0);
    p.resize(n);
    for (auto& i : p) cin >> i.x >> i.y;
}

// Convex Hull
ll ccw(const Point& a, const Point& b, const Point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

ll dist(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool cmp(const Point& p1, const Point& p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}

void grahamScan() {
    sort(p.begin(), p.end());
    sort(p.begin() + 1, p.end(), cmp);
    st.push_back(0);
    st.push_back(1);
    for (int next = 2; next < n; next++) {
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

// get lines
double solve() {
    double ans = 5e8;
    for (int i = 0; i < sz(st); i++) {
        Point u = p[st[i]], v = p[st[(i + 1) % sz(st)]];
        double res = 0;
        if (u.x == v.x) {
            for (int j = 0; j < sz(st); j++) {
                res = max<double>(res, abs(u.x - p[st[j]].x));
            }
            ans = min(ans, res);
        }
        else {
            double a = (double)(v.y - u.y) / (v.x - u.x);
            double b = -1;
            double c = u.y - a * u.x;
            
            for (int j = 0; j < sz(st); j++) {
                res = max(res, abs(a * p[st[j]].x + b * p[st[j]].y + c) / sqrt(a * a + b * b));
            }
            ans = min(ans, res);
        }
    }

    return ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int tt = 1; ; tt++) {
        init();

        input();

        grahamScan();

        cout << "Case " << tt << ": ";
        double ans = solve();
        cout << fixed;
        cout.precision(2);
        cout << ans + 0.00499999 << '\n';
    }
}