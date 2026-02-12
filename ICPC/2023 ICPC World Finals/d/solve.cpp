#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld INF = 4e18;
constexpr ld EPS = 1e-8;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<ld>;

struct Pyramid {
    vector<P> p;
    ld h{};
};

void get_other_points(Pyramid &a) {
    P v{a.p[1] - a.p[0]};
    a.p[2].x = v.dot(P{+1, -1});
    a.p[2].y = v.dot(P{+1, +1});
    a.p[2] = a.p[2] + a.p[0];
    a.p[3].x = v.dot(P{0, -1});
    a.p[3].y = v.dot(P{+1, 0});
    a.p[3] = a.p[3] + a.p[0];
}

P get_tip(const P &a1, const P &a2, const ld h) {
    const P u = (a2 - a1).normal();
    const ld c = hypot((a2 - a1).dist() / 2, h);
    return (a1 + a2) / 2 + u * c;
}

ld segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max((ld)0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}
template<class P> bool onSegment(P s, P e, P p) { return segDist(s, e, p) < EPS; }
template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
        
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

ld get_min_dist(const P &a1, const P &a2, const ld ah, const P &b1, const P &b2, const ld bh, const Pyramid &a, const Pyramid &b) {
    const auto as = get_tip(a1, a2, ah);
    const auto bs = get_tip(b1, b2, bh);

    ld ret = INF;

    const auto ac = segInter(as, bs, a1, a2);
    const auto bc = segInter(as, bs, b1, b2);
    if (!ac.empty() && !bc.empty() && (ac[0] - as).dist() < (bc[0] - as).dist() + EPS) {
        ret = min(ret, (bs - as).dist());
    }

    const vector<P> aa{a1, a2}, bb{b1, b2};
    for (const auto am : aa) {
        if (!segInter(bs, am, b1, b2).empty()) {
            ret = min(ret, (am - as).dist() + (bs - am).dist());
        }
    }
    for (const auto bm : bb) {
        if (!segInter(as, bm, a1, a2).empty()) {
            ret = min(ret, (bm - as).dist() + (bs - bm).dist());
        }
    }
    for (const auto am : aa) {
        for (const auto bm : bb) {
            ret = min(ret, (am - as).dist() + (bm - am).dist() + (bs - bm).dist());
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    Pyramid a{}, b{};
    a.p.assign(4, P{0, 0});
    b.p.assign(4, P{0, 0});
    cin >> a.p[0].x >> a.p[0].y >> a.p[1].x >> a.p[1].y >> a.h;
    cin >> b.p[0].x >> b.p[0].y >> b.p[1].x >> b.p[1].y >> b.h;

    get_other_points(a);
    get_other_points(b);

    // DEBUG
    // for (int i = 0; i < 4; i++) {
    //     cout << b.p[i].x << ' ' << b.p[i].y << '\n';
    //     cout << (b.p[i] - b.p[(i + 1) % 4]).dist() << '\n';
    // }

    ld ans = INF;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            const ld res = get_min_dist(a.p[i], a.p[(i + 1) % 4], a.h, b.p[j], b.p[(j + 1) % 4], b.h, a, b);
            ans = min(ans, res);
        }
    }

    cout << fixed;
    cout.precision(10);
    cout << ans << '\n';
}
