#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt((ld)dist2()); }
};

using P = Point<ll>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<P> a(n);
    for (auto &i : a) cin >> i.x >> i.y;

    auto get_fartest_point = [&](int st) -> int {
        int ret = 0;
        ll d = -1;
        for (int i = 0; i < n; i++) {
            if ((a[i] - a[st]).dist2() > d) {
                ret = i;
                d = (a[i] - a[st]).dist2();
            }
        }
        return ret;
    };

    int st = get_fartest_point(get_fartest_point(0));
    const P o = a[st];

    sort(all(a), [&](const P &i, const P &j) {
        return (i - o).dist2() < (j - o).dist2();
    });

    ld ans = 0;
    for (int i = 0; i + 1 < n; i++) {
        ans += (a[i + 1] - a[i]).dist();
    }

    cout << fixed;
    cout.precision(10);
    cout << ans << '\n';
}
