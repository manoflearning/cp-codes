#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using i128 = __int128_t;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    ll cross(P p) const { return x * p.y - y * p.x; }
};

using P = Point<ll>;

ll polygonArea2(const vector<P> &v) {
    ll a = v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}

ld cal(const int n, const vector<P> &a) {
    const ll pa = polygonArea2(a);

    i128 sum_x{}, sum_y{};
    for (int i = 0; i < n; i++) {
        sum_x += a[i].x;
        sum_y += a[i].y;
    }

    const ll mx = n - 2;

    i128 acc_x{}, acc_y{};
    for (int i = 1; i < n; i++) {
        // acc_x += (mx - 2 * i + 2) * a[i].x;
        // acc_y += (mx - 2 * i + 2) * a[i].y;
        acc_x += (mx - i + 1) * a[i].x;
        acc_y += (mx - i + 1) * a[i].y;
    }

    i128 pt{};
    for (int i = 0; i < n; i++) {
        pt += a[i].x * acc_y - a[i].y * acc_x;

        acc_x -= a[(i + 1) % n].x * mx;
        acc_y -= a[(i + 1) % n].y * mx;

        acc_x += (sum_x - a[i].x - a[(i + 1) % n].x);
        acc_y += (sum_y - a[i].y - a[(i + 1) % n].y);
        
        // acc_x += 2 * (sum_x - a[i].x - a[(i + 1) % n].x);
        // acc_y += 2 * (sum_y - a[i].y - a[(i + 1) % n].y);

        // acc_x -= a[i].x * mx;
        // acc_y -= a[i].y * mx;
    }

    return (ld)pt / pa;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);

    int n; cin >> n;

    vector<P> a(n);
    for (auto &i : a) cin >> i.x >> i.y;

    cout << cal(n, a) << '\n';
}
