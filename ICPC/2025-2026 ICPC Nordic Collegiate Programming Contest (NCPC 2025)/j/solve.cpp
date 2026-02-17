#pragma GCC optimize ("O3, unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

constexpr ll INF = 4e18;

unordered_map<ll, ll> dp;
ll f(const ll t, const ll e, const ll n) {
    if (dp.count({(ll)(t % n + e % n * n)})) return dp[t % n + e % n * n];
    
    // DEBUG
    // cout << "hello\n";
    
    auto &ret = dp[t % n + e % n * n];
    for (ll d = 1; ; d++) {
        ll res = (2 * e - d + 1) * d / 2 % n;
        if ((res + t) % n == 0) {
            return ret = d;
        }
    }
    return ret = INF;
}

tuple<ll, ll, ll> fuck(const ll n, const ll e) {
    unordered_set<ll> vis;

    ll t = 0, diff_e = 0, sum_e = 0, sum_r = 0;
    while (e > 0 && !vis.count(t % n + (e + diff_e) % n * n)) {
        vis.insert(t % n + (e + diff_e) % n * n);

        const ll d = f(t, e + diff_e, n);

        // DEBUG
        // cout << t % n << ' ' << e % n << ' ' << d << '\n';

        if (e + diff_e < d) {
            t += (e + diff_e) * (e + diff_e + 1) / 2;
            break;
        }

        t += (2 * (e + diff_e) - d + 1) * d / 2;

        sum_e += d;
        sum_r += (2 * diff_e - d + 1) * d / 2;
        
        diff_e += 2 - d;
    }

    return {diff_e, sum_e, sum_r};
}

ll naive(const ll n, ll e) {
    const auto [x, y, z] = fuck(n, e);

    ll t = 0;
    if (x < 0) {
        const ll k = e / (-x);
        t += k * e * y + k * (k - 1) / 2 * x * y + k * z;
        e += k * x;
    }

    unordered_set<ll> st;
    while (e > 0) {
        const ll idx = t % n + e % n * n;
        if (st.count(t % n + e * n)) return -1;
        st.insert(t % n + e * n);
        const ll d = f(t, e, n);

        // DEBUG
        // cout << t % n << ' ' << e % n << ' ' << d << '\n';

        if (e < d) {
            t += e * (e + 1) / 2;
            break;
        }

        t += (2 * e - d + 1) * d / 2;
        e += 2 - d;
    }
    return t;
}

// string i128_to_string(i128 x) {
//     string s;
//     while (x > 0) {
//         s.push_back(x % 10 + '0');
//         x /= 10;
//     }
//     reverse(all(s));
//     return s;
// }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // TEST
    // for (ll n = 2; n <= 2; n++)
    // for (ll e = (ll)1; e <= (ll)1e7; e++) {
    // dp.clear();

    ll n, e;
    cin >> n >> e;

    if (n == 1) {
        cout << "infinity\n";
        exit(0);
    }

    ll ans = naive(n, e);
    if (ans == -1) {
        cout << "infinity\n";
    } else {
        cout << ans << '\n';
    }

    // cout.flush();
    // }
}
