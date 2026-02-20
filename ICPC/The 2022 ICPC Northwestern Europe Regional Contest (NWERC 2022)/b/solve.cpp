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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);

    ll h, r, da, dw;
    cin >> h >> r >> da >> dw;

    ld lo = 0, hi = h;
    for (int t = 0; t < 100'000; t++) {
        const ld mid1 = (2 * lo + hi) / 3;
        const ld mid2 = (lo + 2 * hi) / 3;

        auto f = [&](ld x) {
            return (x * x * dw + (h + x) * (h - x) * da) / (x * dw + (h - x) * da);
        };

        if (f(mid1) <= f(mid2)) hi = mid2;
        else lo = mid1;
    }

    cout << lo << '\n';
}
