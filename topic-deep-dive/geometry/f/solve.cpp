#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld EPS1 = 1e-8;
constexpr ld EPS2 = 5e-7;
constexpr ld ZERO = 0;
constexpr ld INF = 1e18;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	P operator-(P p) const { return P(x-p.x, y-p.y); }
};

using P = Point<ld>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ld x, y, z;
    cin >> x >> y >> z;

    if (x > y) swap(x, y);
    if (y > z) swap(y, z);
    if (x > y) swap(x, y);

    P p0{0, 0}, p1{x, x + 2 * z}, p2{x + y + z, x + y + z};

    const ld a = hypot(p1.x, p1.y);
    const ld b = hypot(p2.x, p2.y);
    const ld c = hypot((p2 - p1).x, (p2 - p1).y);

    const ld p = (a + b + c) / 2;
    const ld A = sqrt(p * (p - a) * (p - b) * (p - c));

    ld ans = a * b * c / (4 * A);
    ans = max(ans, hypot(x + y, z));

    cout << fixed;
    cout.precision(15);
    cout << ans << '\n';

    return 0;
}
