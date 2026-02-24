#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ld INF = 4e18;
constexpr ld EPS = 1e-9;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);

    vector<ll> t(4);
    for (auto &i : t) cin >> i;

    vector<int> ord(4);
    iota(all(ord), 0);

    ld opt{-INF};
    vector<int> opt_ord;
    vector<ld> opt_a;

    do {
        vector<ld> a(4);
        for (int i = 0; i < 4; i++) a[i] = t[ord[i]] - 1;

        const ld lhs = a[0] * a[3];
        const ld rhs = a[1] * a[2];

        if (lhs + EPS < rhs) {
            if (lhs / a[2] + a[2] > a[1] + lhs / a[1]) {
                a[1] = lhs / a[2];
            } else {
                a[2] = lhs / a[1];
            }
        }
        if (lhs > rhs + EPS) {
            if (rhs / a[0] + a[3] > a[0] + rhs / a[3]) {
                a[0] = rhs / a[3];
            } else {
                a[3] = rhs / a[0];
            }
        }

        // if (opt < min(lhs, rhs)) {
        //     opt = min(lhs, rhs);
        //     opt_ord = ord;
        //     opt_a = a;
        // }
        if (opt < (a[0] + 1) * (a[3] + 1) + (a[1] + 1) + (a[2] + 1)) {
            opt = (a[0] + 1) * (a[3] + 1) + (a[1] + 1) + (a[2] + 1);
            opt_ord = ord;
            opt_a = a;
        }
    } while (next_permutation(all(ord)));

    assert(!opt_ord.empty());

    for (auto &i : opt_ord) cout << i + 1 << ' ';
    cout << '\n';
    for (auto &i : opt_a) cout << i + 1.0l << ' ';
    cout << '\n';
}