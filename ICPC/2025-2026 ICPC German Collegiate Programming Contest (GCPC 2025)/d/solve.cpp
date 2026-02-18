#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 1e18;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
};

using P = Point<ll>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<P> a(n);
    for (auto &i : a) cin >> i.x >> i.y;

    ll mn_x{INF}, mx_x{-INF}, mn_y{INF}, mx_y{-INF};
    for (auto &i : a) {
        mn_x = min(mn_x, i.x);
        mx_x = max(mx_x, i.x);
        mn_y = min(mn_y, i.y);
        mx_y = max(mx_y, i.y);
    }
    cout << 4 << '\n';
    cout << mn_x << ' ' << mn_y << '\n';
    cout << mx_x << ' ' << mn_y << '\n';
    cout << mx_x << ' ' << mx_y << '\n';
    cout << mn_x << ' ' << mx_y << '\n';
}
