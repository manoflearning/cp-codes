#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld EPS = 1e-10l;

struct Frac {
    ll n, d;
    Frac() : n{}, d{} {}
    Frac(ll x) : n{x}, d{1} {}
    Frac(string s) {
        string acc;
        for (int i = 0; i < sz(s); i++) {
            if (s[i] == '/') {
                n = stoll(acc);
                acc.clear();
            } else {
                acc.push_back(s[i]);
            }
        }
        d = stoll(acc);
    }

    Frac operator-(const Frac &rhs) const {
        Frac ret{};
        ret.n = n * rhs.d - rhs.n * d;
        ret.d = d * rhs.d;
        return ret;
    }
    Frac operator-(ll rhs) const {
        Frac ret{};
        ret.n = n - rhs * d;
        ret.d = d;
        return ret;
    }
    Frac operator*(const Frac &rhs) const {
        Frac ret{};
        ret.n = n * rhs.n;
        ret.d = d * rhs.d;
        return ret;
    }
    ld operator/(ld rhs) const {
        return (ld)n / d / rhs;
    }
};

struct P {
    ll x, y;
    P(ll x = 0, ll y = 0) : x{}, y{} {}

    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }

    ll cross(P p) const { return x * p.y - y * p.x; }
    // Frac cross(Point<Frac> p) const { return x * p.y - y * p.x; }
    ll dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt((ld)dist2()); }
};

struct Q {
    Frac x, y;

    Q operator-(P p) const { return Q(x - p.x, y - p.y); }
    Q operator-(Q p) const { return Q(x - p.x, y - p.y); }

    Frac cross(P p) const { return x * p.y - y * p.x; }
    // Frac cross(Point<Frac> p) const { return x * p.y - y * p.x; }
    Frac dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt((ld)dist2()); }
};


ld lineDist(const P &a, const P &b, const Q &p) {
    return (b - a).cross(p - a) / (b - a).dist();
}
ld lineDist(const P &a, const P &b, const P &p) {
    return (b - a).cross(p - a) / (b - a).dist();
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        vector<P> a(3);
        for (auto &i : a) cin >> i.x >> i.y;

        string _x, _y;
        cin >> _x >> _y;

        Q d{Frac(_x), Frac(_y)};

        a.push_back(a[1] - a[0] + a[2]);
        ld dist = lineDist(a[0], a[1], d) + lineDist(a[1], a[2], d);

        bool yes = 1;
        yes &= (abs(dist - lineDist(a[0], a[1], a[2])) < EPS);

        bool res = 0;
        vector<int> ord(3);
        iota(all(ord), 0);
        do {
            const ld d1 = lineDist(a[ord[0]], a[ord[1]], a[ord[2]]);
            const ld d2 = lineDist(a[ord[0]], a[ord[1]], d);

            ll lo = 0, hi = 1e12;
            while (lo < hi) {
                const ll mid = (lo + hi) >> 1;
                if (d1 * mid < d2 + EPS) lo = mid + 1;
                else hi = mid;
            }

            res |= (abs(d1 * lo - d2) < EPS);
        } while (next_permutation(all(ord)));

        yes &= res;

        cout << (yes ? "Yes" : "No") << '\n';
    }
}
