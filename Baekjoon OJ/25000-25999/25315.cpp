#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>

struct Point {
    ll x, y;
};

struct Line {
    Point s, e;
    ll t;
};

int n;
vector<Line> l;
ll ans;

//ccw 알고리즘
ll ccw(Point a, Point b, Point c) {
	//양수를 반환하면 ccw, 음수를 반환하면 cw, 0을 반환하면 a, b, c는 한 직선 위에 있다.
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

//두 선분 l1과 l2가 교차하는가?
bool isCrossed(Line l1, Line l2) {
    Point a = l1.s, b = l1.e, c = l2.s, d = l2.e;

    ll ab = ccw(a, b, c) * ccw(a, b, d);
    ll cd = ccw(c, d, a) * ccw(c, d, b);

	return (ab <= 0 && cd <= 0);
}

void input() {
    cin >> n;
    l.resize(n);
    for (auto& i : l) {
        cin >> i.s.x >> i.s.y;
        cin >> i.e.x >> i.e.y;
        cin >> i.t;
    }
}

void solve() {
    for (int i = 0; i < n; i++) ans += l[i].t;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (isCrossed(l[i], l[j])) {
                ans += min(l[i].t, l[j].t);
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input(); 

    solve();

    cout << ans;

	return 0;
}