// 만약 세 점이 한 직선 위에 있다면, 무조건 그 직선대로 쏴야한다
// 

//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Point { ll x, y; };

int n;
vector<Point> a;

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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    a.resize(n);
    for (auto& i : a) 
        cin >> i.x >> i.y;
    
    if (n <= 4) {
        cout << "success";
        return 0;
    }
    
    sort(all(a), [&](const Point& lhs, const Point& rhs) {
        if (lhs.x ^ rhs.x) return lhs.x < rhs.x;
        return lhs.y < rhs.y;
    });

    sort(a.begin() + 1, a.end(), cmp);

    vector<Point> b;
    Point p1 = { INF, INF }, p2 = { INF, INF };
    for (int i = 1; i + 1 < sz(a); i++) {
        if (ccw(a[0], a[i], a[i + 1]) == 0) {
            p1 = a[i], p2 = a[i + 1];
            break;
        }
    }

    if (p1.x == INF) {
        cout << "failure";
        return 0;
    }

    for (int i = 1; i < sz(a); i++) {
        if (ccw(p1, p2, a[i])) b.push_back(a[i]);
    }

    if (sz(b) <= 2) {
        cout << "success";
        return 0;
    }

    for (int i = 2; i < sz(b); i++) {
        if (ccw(b[0], b[1], b[i])) {
            cout << "failure";
            return 0;
        }
    }

    cout << "success";

	return 0;
}