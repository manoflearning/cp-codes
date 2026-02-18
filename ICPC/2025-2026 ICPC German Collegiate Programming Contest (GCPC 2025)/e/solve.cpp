#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld PI = 3.14159265358979323846264338327950288l;
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
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<ld>;

ld get_angle(P a, P b) { return acos(a.dot(b) / (a.dist() * b.dist())); }

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);

    int n; cin >> n;
    vector<P> a(n);
    for (auto &i : a) cin >> i.x >> i.y;

    for (int i = 0; i < 4; i++) a.push_back(a[i]);

    ld ans{};
    for (int i = 0; i < n; i++) {
        ld res{};
        const ld t1 = get_angle(a[i] - a[i + 1], a[i + 3] - a[i + 1]);
        const ld t2 = get_angle(a[i + 1] - a[i + 3], a[i + 4] - a[i + 3]);
        const ld l = (a[i + 1] - a[i + 3]).dist();

        // assert(t1 + t2 >= PI / 2 - EPS);

        const ld lb1 = PI / 2 - t1, ub1 = PI - t1;
        const ld lb2 = PI / 2 - (PI - t2), ub2 = PI / 2 - (PI / 2 - t2);
 
        const ld lb = max(lb1, lb2), ub = min(ub1, ub2);
        if (lb <= PI / 4 + EPS && PI / 4 - EPS <= ub) {
            res += sqrt(2.0l) * l;
        } else if (ub < PI / 4 + EPS) {
            res += (sin(ub) + cos(ub)) * l;
        } else if (PI / 4 + EPS < lb) {
            res += (sin(lb) + cos(lb)) * l;
        } else { /* assert(0); */ }

        if ((a[i] - a[i + 1]).cross(a[i + 4] - a[i + 3]) < -EPS) {
            const auto [_, p] = lineInter(a[i], a[i + 1], a[i + 3], a[i + 4]);
            res = min(res, (a[i + 1] - p).dist() + (a[i + 3] - p).dist());
        }

        res -= (a[i + 1] - a[i + 2]).dist() + (a[i + 3] - a[i + 2]).dist();
        
        // assert(res > -EPS);
        ans = max(ans, res);
    }
    cout << ans << '\n';
}
