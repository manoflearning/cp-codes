#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int N = 3'000'000;
constexpr ll INF = 1e9;

ll naive(ll n) {
    if (n % 10 == 0) return -1;

    ll x;
    for (x = n; x <= INF; x += n) {
        bool yes = 1;
        string s = to_string(x);
        for (int i = 0; i + 1 < sz(s); i++) {
            yes &= s[i] <= s[i + 1];
        }
        if (yes) return x;
    }
    return x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    vector<ll> fuck;
    ll max_cnt = 0;
    for (ll n = 1; n <= N; n++) {
        const ll res = naive(n);
        const ll cnt = res / n;
        // max_cnt = max(max_cnt, cnt);
        if (INF < res) fuck.push_back(n);
        // cout << n << ' ' << res << ' ' << cnt << '\n';
    }
    // cout << "max(cnt) = " << max_cnt << '\n';
    cout << sz(fuck) << '\n';
    for (auto &i : fuck) cout << i << '\n';

    return 0;
}
