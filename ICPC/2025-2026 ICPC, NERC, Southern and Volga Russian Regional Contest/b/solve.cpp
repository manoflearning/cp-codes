#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

using P = Point<ll>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<P> a(n);
        for (auto &i : a) cin >> i.x >> i.y;

        reverse(all(a));

        int ans = 0;
        int j = 1;
        for (int i = 0; i + 2 < n; i++) {
            if (j <= i + 1) j = i + 2;
            while (j < n) {
                bool yes = 1;
                yes &= (a[i].cross(a[j - 1], a[j]) > 0);
                yes &= (a[j - 2].cross(a[j - 1], a[j]) > 0);
                yes &= (a[i + 1].cross(a[i], a[j]) < 0);
                if (!yes) break;
                j++;
            }
            ans = max(ans, j - i);
        }
        cout << (ans >= 3 ? ans : 0) << '\n';
    }
}