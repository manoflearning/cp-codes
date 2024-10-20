#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct point {
	ll x, y;
    int idx;
	bool operator<(const point& rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
};

int n;
vector<point> p;

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

ll dist(const point& p1, const point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool cmp(const point& p1, const point& p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}

bool cmp2(const point& p1, const point& p2) {
    return dist(p[0], p1) > dist(p[0], p2);
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i].x >> p[i].y;
            p[i].idx = i;
        }

        sort(p.begin(), p.end());
        sort(p.begin() + 1, p.end(), cmp);

        int st = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (ccw(p[0], p[i - 1], p[i]) != 0) {
                st = i; break;
            }
        }

        sort(p.begin() + st, p.end(), cmp2);

        for (int i = 0; i < n; i++)
            cout << p[i].idx << ' ';
        cout << '\n';
    }

	return 0;
}