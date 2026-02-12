#pragma GCC optmize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using ld = long double;

template <class T> int sgn(T x) { return (x>0) -  (x<0); }
template <class T>
struct Point{
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator< (P p) const { return tie(x,y) < tie(p.x, p.y); }
    bool operator== (P p) const { return tie(x,y) == tie(p.x, p.y); }
    P operator+ (P p) const { return P(x+p.x, y+p.y); }
    P operator- (P p) const { return P(x-p.x, y-p.y); }
    P operator* (T d) const { return P(x * d, y * d); }
    P operator/ (T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    ld dist() const { return sqrtl((ld)dist2()); }
    double angle() const { return atan(y, x); }
    P unit() const { return *this/dist(); }
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<ld> P;
vector<P> convexHull(vector<P> pts) {
    if(sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<P> h(sz(pts) + 1);
    int s = 0, t = 0;
    for(int it = 2; it--; s = --t, reverse(all(pts))) {
        for(P p: pts) { 
            while(t >= s+2 && h[t-2].cross(h[t-1], p) <=0) t--;
            h[t++] = p;
        }
    }

    return {h.begin(), h.begin() + t - (t==2 && h[0] == h[1])};
}

vi getdie() {
    int n; cin >> n;
    vi arr(n); for(auto &a:arr) cin >> a;
    sort(all(arr));
    return arr;
}

bool win(const vi& d1, const vi& d2) {
    ll ac = (ll)sz(d1) * sz(d2) * 2;
    ll wr = 0;

    for(auto &a:d1) {
        int l = lower_bound(all(d2), a) - d2.begin();
        int r = upper_bound(all(d2), a) - d2.begin();

        wr += l + r;
    }

    return wr*2 > ac;
}

ll wins(const vi& d1, int t) {
    int l = lower_bound(all(d1), t) - d1.begin();
    int r = upper_bound(all(d1), t) - d1.begin();
    return l + r;
}

ld gety(ld x1, ld y1, ld x2, ld y2) {
    return y1 + (y2-y1)*(0.5l - x1)/(x2-x1); 
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cin.exceptions(cin.failbit);

    auto d1 = getdie();
    auto d2 = getdie();

    if(win(d2, d1)) swap(d1, d2);

    vector<int> vx;
    for(auto &a:d1) {
        vx.push_back(a-1);
        vx.push_back(a);
        vx.push_back(a+1);
    }
    for(auto &a:d2) {
        vx.push_back(a-1);
        vx.push_back(a);
        vx.push_back(a+1);
    }

    sort(all(vx)); vx.erase(unique(all(vx)), vx.end());
    reverse(all(vx)); if(vx.back() == 0) vx.pop_back();
    reverse(all(vx));

    vector<P> pts;

    for(auto &x : vx) {
        ll n1 = 0, n2 = 0;

        n1 = wins(d1, x);
        n2 = wins(d2, x);

        ld p1 = (ld)n1 / sz(d1) / 2;
        ld p2 = (ld)n2 / sz(d2) / 2;

        pts.push_back(P{p1, p2});
    }

    auto cv = convexHull(pts);
    const int n = sz(cv);

    ld mn = 1l, mx = 0l;

    for(int i = 0; i < n; i++){
        int j = (i+1) % n;

        // cout << cv[i].x << ' ' << cv[i].y << '\n';

        if((cv[i].x <= 0.5l && cv[j].x >= 0.5l) || (cv[i].x >= 0.5l && cv[j].x <= 0.5l)) {
            if(cv[i].x != cv[j].x) mn = min(mn, gety(cv[i].x, cv[i].y, cv[j].x, cv[j].y));
        }

        if((cv[i].y <= 0.5l && cv[j].y >= 0.5l) || (cv[i].y >= 0.5l && cv[j].y <= 0.5l)) {
            if(cv[i].y != cv[j].y) mx = max(mx, gety(cv[i].y, cv[i].x, cv[j].y, cv[j].x));
        }
    }

    cout << fixed;
    cout.precision(6);
    cout << mn << ' ' << mx << '\n';
}
