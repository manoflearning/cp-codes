// assumption:
// - if answer exists, answer s.t. at least one vertex is in the given points exists

// (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)
// = (p2.x*p3.y - p3.x*p2.y) + (p2.y-p3.y)*p1.x + (p2.x-p3.x)*p1.y + 2p1.x*p1.y

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 202020;

struct Point { ll x, y; };

int n;
vector<Point> a(MAXN);
vector<ll> psum(MAXN);

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    a[0] = a[n];
}

// ll area_triangular(const Point& p1, const Point& p2, const Point& p3) {
//     return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
// }

void construct_psum() {
    for (int i = 1; i <= n; i++) {
        psum[i] = (a[i - 1].x * a[i].y - a[i].x * a[i - 1].y) + psum[i - 1];
    }
}

ll area_convex_polygon(int st, int en) {
    if (st > en) return area_convex_polygon(1, en) + area_convex_polygon(st, n);

    if (st == en) return 0;
    if (st + 1 == en) return 0;

    ll ret = 0;
    ret += psum[en] - psum[st + 1];
    ret += (a[st + 1].y - a[en].y) * a[st].x;
    ret += (a[st + 1].x - a[en].x) * a[st].y;
    ret += 2 * (en - st - 1) * a[st].x * a[st].y;

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    construct_psum();

    cout << area_convex_polygon(1, 3) << '\n';
}
