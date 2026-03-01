#pragma GCC optimize ("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll n, m;
    int k;
    cin >> n >> k >> m;

    vector<vector<pii>> a(k);
    for (auto &i : a) {
        int c; cin >> c;
        i.assign(c, {0, 0});
        for (auto &j : i) cin >> j.first >> j.second, j.second++;
    }

    vector<int> cc;
    for (auto &i : a) for (auto &j : i) {
        cc.push_back(j.first);
        cc.push_back(j.second);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (auto &i : a) for (auto &j : i) {
        j.first = lower_bound(all(cc), j.first) - cc.begin();
        j.second = lower_bound(all(cc), j.second) - cc.begin();
    }

    vector<int> pxor(sz(cc));
    for (int i = 0; i < k; i++) for (const auto &j : a[i]) {
        pxor[j.first] ^= (1 << i);
        pxor[j.second] ^= (1 << i);
    }

    ll sum = 0;
    vector<ll> dp1(1 << k), dp2(1 << k);
    vector<vector<ll>> dp(k + 1, vector<ll>(1 << k));

    for (int i = 0; i + 1 < sz(cc); i++) {
        pxor[i + 1] ^= pxor[i];

        const int bit = pxor[i];
        const ll w = cc[i + 1] - cc[i];

        const int cnt = __builtin_popcount(bit);
        if (cnt < 2) continue;

        dp1[bit] += w, sum += w;

        const int rem = (1 << k) - 1 - bit;
        
        dp[k][rem] += w;
        for (int b = 0; b < k; b++)
            if (bit & (1 << b)) dp[b][rem | (1 << b)] += w;
    }

    auto prop = [&](vector<ll> &D, const int fixed) {
        for (int b = 0; b < k; b++) {
            if (fixed == b) continue;
            for (int i = (1 << k) - 1; i >= 0; i--) {
                if (i & (1 << b)) {
                    D[i ^ (1 << b)] += D[i];
                }
            }
        }
    };

    for (int i = 0; i <= k; i++) prop(dp[i], i);

    int ans = 0;
    for (int bit = 0; bit < (1 << k); bit++) {
        ll res = sum;
        for (int b = 0; b < k; b++)
            if (bit & (1 << b)) res -= dp[b][bit];
        res -= dp[k][bit];
        ans += (res >= m);
    }
    cout << ans << '\n';
}
