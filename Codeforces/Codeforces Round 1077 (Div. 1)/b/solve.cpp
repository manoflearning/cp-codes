#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

pair<ll, ll> solve(ll x, ll y) {
    ll opt_p = 0;

    ll pref = 0, suf = (1ll << 31) - 1 - y;
    for (int b = 30; b >= 0; b--) {
        if ((1 << b) & suf) suf -= (1 << b);

        if ((1 << b) & y) {
            if ((1 << b) & x) {
                pref |= suf;
                break;
            }
        } else {
            if ((1 << b) & x) {
                if (abs(x - opt_p) > abs(x - (pref + suf))) {
                    opt_p = pref + suf;
                }
                pref |= (1 << b);
            } else {
                if (abs(x - opt_p) > abs(x - (pref + (1 << b)))) {
                    opt_p = pref + (1 << b);
                }
            }
        }
    }

    if (abs(x - opt_p) > abs(x - pref)) opt_p = pref;

    assert(!(opt_p & y));
    return {opt_p, y};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        ll x, y;
        cin >> x >> y;

        // ll p = 0, q = 0;
        // bool hit_ub_p = 1, hit_ub_q = 1;

        // for (int b = 30; b >= 0; b--) {
        //     const int bit = (1 << b);
        //     const int mask = bit - 1;

        //     if ((bit & x) && (bit & y)) {
        //         p += bit;
        //         q += bit - 1;
        //         break;
        //     } else if (bit & x) {
        //         p += bit;
        //     } else if (bit & y) {
        //         q += bit;
        //     } else {
        //         if ((mask & p & q) == 0) {
        //             continue;
        //         } else {

        //         }
        //     }
        // }
        // cout << p << ' ' << q << '\n';

    // for (ll x = 0; x <= 1000; x++)
    // for (ll y = 0; y <= 1000; y++) {
        auto res1 = solve(x, y);
        auto res2 = solve(y, x);
        swap(res2.first, res2.second);

        const ll x1 = abs(x - res1.first) + abs(y - res1.second);
        const ll x2 = abs(x - res2.first) + abs(y - res2.second);

        if (x1 > x2) {
            res1 = res2;
            // cout << "x = " << x << ", y = " << y << "\t";
            // cout << res1.first << ' ' << res1.second << ' ' << res2.first << ' ' << res2.second << '\n';
        }

        cout << res1.first << ' ' << res1.second << '\n';
    }
}
