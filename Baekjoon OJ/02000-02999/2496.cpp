#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define pii pair<int, int>

struct Point {
    ll x, y;
};

int n, m, t, d;
vector<Point> p;
vector<Point> bo;

ll ccw(const Point& a, const Point& b, const Point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

void input() {
    cin >> n >> m >> t >> d;
    for (int i = 0; i < t; i++) {
        ll x, y;
        cin >> x >> y;
        p.push_back({ x + y, x - y });
    }
    bo.push_back({ 0, 0 });
    bo.push_back({ n, n });
    bo.push_back({ n + m, n - m });
    bo.push_back({ m, -m });
}

int f(Point lb) {
    int ret = 0;
    for (auto& i : p) {
        if (lb.x <= i.x && i.x <= lb.x + d && lb.y <= i.y && i.y <= lb.y + d) ret++;
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

    input();

    int mx = 0;
    Point ans = { 0, 0 };
    for (auto& i : p) {
        for (auto& j : p) {
            if (j.x < i.x) continue;
            if (i.y < j.y) continue;

            Point lb = { i.x, j.y };
            
            queue<Point> q;
            if ((lb.x + lb.y) & 1) {
                q.push({ lb.x - 1, lb.y });
                q.push({ lb.x + 1, lb.y });
                q.push({ lb.x, lb.y - 1 });
                q.push({ lb.x, lb.y + 1 });
            }
            else q.push({ lb.x, lb.y });
            
            while (sz(q)) {
                Point now = q.front();
                q.pop();
                
                if (now.x + now.y + d > 2 * n) {
                    now.x = now.x - d / 2;
                    now.y = now.y - d / 2;
                }
                
                int res = f(now);
                if (res > mx) {
                    mx = res;
                    ans = { now.x + d / 2, now.y + d / 2 };
                }
            }
        }
    }
    
    cout << (ans.x + ans.y) / 2 << ' ' << (ans.x - ans.y) / 2 << '\n';
    cout << mx;

    return 0;
}