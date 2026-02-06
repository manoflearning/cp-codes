#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll ,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define fr first
#define sc second

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const {return tie(x, y) < tie(p.x, p.y);}
    bool operator==(P p) const {return tie(x, y) == tie(p.x, p.y);}
    P operator+(P p) const {return P(x + p.x, y + p.y);}
    P operator-(P p) const {return P(x - p.x, y - p.y);}
    P operator*(T d) const {return P(x * d, y * d);}
    P operator/(T d) const {return P(x / d, y / d);}
    T dot(P p) const {return x * p.x + y * p.y;}
    T cross(P p) const {return x * p.y - y * p.x;}
    T cross(P a, P b) const {return (a-*this).cross(b-*this);}
    T dist2() const {return x * x + y * y;}
    ld dist() const {return sqrt((ld)dist2());}
    P unit() const {return *this / dist();}
    P perp() const {return P(-y, x);}
    P normal() const {return perp().unit();}
    P rotate(ld a) const {return P(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a));}
};
void solve() {
    vl a(3);
    rep(i, 0, 3) cin >> a[i];
    sort(all(a));

    Point<ll> org(0, 0);
    Point<ll> P(a[0], a[0]+2*a[2]), Q(a[0]+a[1]+a[2], a[0]+a[1]+a[2]);
    ld A = hypot(P.x, P.y);
    ld B = hypot(Q.x, Q.y);
    ld C = hypot((Q-P).x, (Q-P).y);
    ld S = fabsl(org.cross(P, Q) / 2.0L);
    ld ans = ((A * B * C) / (4 * S));
    ans = max(ans, hypot((ld)a[0] + a[1], (ld)a[2]));
    cout << fixed << setprecision(10);
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; tc = 1;
    while(tc --> 0) {
        solve();
    }
    return 0;
}