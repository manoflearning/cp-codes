#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld EPS = 1e-8;
constexpr ld PI = 3.14159265358979323846264338327950288l;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);

// TEST
// for (int s = 1; s <= 100'000; s++) {
// cout << "s = " << s << ", ";

    int s; cin >> s;

    ld lo = 0, hi = 5 * sqrt(s / PI);
    for (int t = 0; t < 100; t++) {
        const ld r = (lo + hi) / 2;

        ll cnt = 0;

        ll pw{};
        for (ll h = floor(r) + EPS; h >= 1; h--) {
            const ll w = floor(sqrt(r * r - h * h)) + EPS;
            cnt += h * (w - pw);
            pw = w;
        }

        cnt *= 4;

        if (cnt > s) hi = r;
        else lo = r;
    }

    // if (lo > 5 * sqrt(s / PI) || lo < sqrt(s / PI)) {
    //     cout << s << ' ' << lo << ' ' << 2 * sqrt(s / PI) << '\n';
    //     cout.flush();
    //     assert(0);
    // }
    cout << lo << '\n';
// }
}
