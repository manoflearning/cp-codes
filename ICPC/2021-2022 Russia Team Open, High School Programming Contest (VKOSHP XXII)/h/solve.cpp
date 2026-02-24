#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld INF = 1e12;
constexpr ld EPS = 1e-8;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);

    int n; cin >> n;
    vector<tuple<ll, ll, ll>> pos, neg;
    for (int i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a > 0) pos.push_back({a, b, c});
        else neg.push_back({a, b, c});
    }

    ld l = -INF, r = INF;
    for (int t = 0; t < 500; t++) {
        const ld x1 = (2 * l + r) / 3;
        const ld x2 = (l + 2 * r) / 3;

        ld lb1{-INF}, ub1{INF}, lb2{-INF}, ub2{INF};
        for (auto [a, b, c] : pos) {
            lb1 = max(lb1, a * x1 * x1 + b * x1 + c);
            lb2 = max(lb2, a * x2 * x2 + b * x2 + c);
        }
        for (auto [a, b, c] : neg) {
            ub1 = min(ub1, a * x1 * x1 + b * x1 + c);
            ub2 = min(ub2, a * x2 * x2 + b * x2 + c);
            if (ub1 - lb1 < -EPS || ub2 - lb2 < -EPS) break;
        }

        if (ub1 - lb1 < ub2 - lb2) l = x1;
        else r = x2;
    }

    ld x{l}, y{-INF};
    for (auto [a, b, c] : pos) {
        y = max(y, a * x * x + b * x + c);
    }

    cout << x << ' ' << y << '\n';
}