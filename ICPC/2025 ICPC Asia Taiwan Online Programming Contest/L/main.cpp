#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

bool operator<=(const pll& lhs, const pll& rhs) {
    if(lhs.fr == rhs.fr) return lhs.sc <= rhs.sc;
    return lhs.fr <= rhs.fr;
}
inline ll ccw(pll a, pll b, pll c) {
    ll x = (b.fr-a.fr)*(c.sc-a.sc)-(c.fr-a.fr)*(b.sc-a.sc);
    return (x > 0) - (x < 0);
}
bool seg_intersect(pll a, pll b, pll c, pll d) {
    if(a > b) swap(a, b);
    if(c > d) swap(c, d);

    ll c1 = ccw(a, b, c) * ccw(a, b, d);
    ll c2 = ccw(c, d, a) * ccw(c, d, b);

    if(c1 == 0 && c2 == 0) {
        return (a <= d && c <= b);
    }
    return (c1 <= 0 && c2 <= 0);
}
inline bool in(pll a, pll b, pll c) {
    return (a.fr <= c.fr && c.fr <= b.fr) && (a.sc <= c.sc && c.sc <= b.sc);
}
bool solve() {
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    pll a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
    pll p, q; cin >> p.fr >> p.sc >> q.fr >> q.sc;

    if(seg_intersect(a, b, p, q)) return true;
    if(seg_intersect(b, c, p, q)) return true;
    if(seg_intersect(d, c, p, q)) return true;
    if(seg_intersect(a, d, p, q)) return true;

    if(in(a, c, p) || in(a, c, q)) return true;
    return false;
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cout << (solve() ? "STOP" : "OK") << '\n';
    }
}
