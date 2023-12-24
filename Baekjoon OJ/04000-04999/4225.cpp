#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Line {
    ll a, b, c; // ax + by + c = 0
};

struct Point {
    ll x, y;
    double dist(Line line) { // |ax + by + c| / sqrt(a^2 + b^2)
        assert(line.a != 0 || line.b != 0);
        double ret = abs(line.a * x + line.b * y + line.c);
        ret /= sqrt(line.a * line.a + line.b * line.b);
        return ret;
    }
    bool operator<(const Point& rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
};

int n;
vector<Point> a;
vector<Line> b;
vector<int> st;

void init() {
    a.clear();
    b.clear();
    st.clear();
}

void input() {
    cin >> n;
    if (n == 0) exit(0);
    a.resize(n);
    for (auto& i : a) cin >> i.x >> i.y;
}

ll ccw(const Point& a, const Point& b, const Point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
ll dist(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool cmp(const Point& p1, const Point& p2) {
    return (ccw(a[0], p1, p2) > 0 || (ccw(a[0], p1, p2) == 0 && dist(a[0], p1) < dist(a[0], p2)));
}
void grahamScan() {
	sort(a.begin(), a.end());
	sort(a.begin() + 1, a.end(), cmp);
	st.push_back(0);
	st.push_back(1);
	for (int next = 2; next < n; next++) {
		while (st.size() >= 2) {
			int first = st.back();
			st.pop_back();
			int second = st.back();
			if (ccw(a[second], a[first], a[next]) > 0) {
				st.push_back(first);
				break;
			}
		}
		st.push_back(next);
	}
}

double solve() {
    double ret = 1e18;

    for (int i = 0; i < sz(st); i++) {
        Point u = a[st[i]], v = a[st[(i + 1) % sz(st)]];
        b.push_back({ 
            u.y - v.y, 
            -(u.x - v.x), 
            -u.x * (u.y - v.y) + u.y * (u.x - v.x)
        });
    }

    for (auto& line : b) {
        double res = 0;
        for (auto& point : a) {
            res = max(res, point.dist(line));
        }
        ret = min(ret, res);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cout << fixed;
    cout.precision(2);

    while (1) {
        init();

        input();

        grahamScan();

        double res = solve();
        int ans = ceil(res * 100);
        cout << (double)ans / 100 << '\n';
    }
}