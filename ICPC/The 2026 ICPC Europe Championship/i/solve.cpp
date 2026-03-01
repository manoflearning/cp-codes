#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld INF = 4e18l;

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
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
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

vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
    reverse(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
    for (P p : pts) {
        while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
        h[t++] = p;
    }
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(15);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<vector<ll>> a(n);
        for (auto &i : a) {
            int k; cin >> k;
            i.assign(k, 0);
            for (auto &j : i) cin >> j;
        }

        ld ans1{+INF}, ans2{-INF};
        vector<P> b;
        for (auto &i : a) {
            ld m{}, r{};
            for (auto &j : i) m += j, r += j * j;
            m /= sz(i), r /= sz(i);
            b.push_back(P{m, r});
            ans1 = min(ans1, r - m * m);
            ans2 = max(ans2, r - m * m);
        }

        b = convexHull(b);
        reverse(all(b));

        for (int i = 0; i + 1 < sz(b); i++) {
            const ld p = (b[i + 1].y - b[i].y) / (b[i + 1].x - b[i].x);
            const ld q = b[i].y - p * b[i].x;

            auto cal = [](ld p, ld q, ld x) -> ld {
                return -x * x + p * x + q;
            };
    
            if (b[i].x <= p / 2 && p / 2 <= b[i + 1].x) {
                ans2 = max(ans2, cal(p, q, p / 2));
            }
        }

        cout << ans1 << ' ' << ans2 << '\n';
    }
}
