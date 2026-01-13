#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

// what: probabilistic substring matching using double rolling hash.
// time: build O(n), get O(1), match O(n); memory: O(n)
// constraint: probabilistic (hash collision), returns 0-indexed match positions.
// usage: auto pos = rk_match(t, p); // p in t
struct rabin_karp {
    static constexpr ll MOD1 = 1000000007;
    static constexpr ll MOD2 = 1000000009;
    static constexpr ll BASE = 911382323;
    vector<ll> p1, p2, h1, h2;

    void build(const string &s) {
        // goal: precompute prefix hashes and powers.
        int n = sz(s);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            ll x = (unsigned char)s[i] + 1;
            p1[i + 1] = p1[i] * BASE % MOD1;
            p2[i + 1] = p2[i] * BASE % MOD2;
            h1[i + 1] = (h1[i] * BASE + x) % MOD1;
            h2[i + 1] = (h2[i] * BASE + x) % MOD2;
        }
    }
    pll get(int l, int r) const { // [l, r)
        // result: hash of s[l..r).
        ll x1 = (h1[r] - h1[l] * p1[r - l]) % MOD1;
        ll x2 = (h2[r] - h2[l] * p2[r - l]) % MOD2;
        if (x1 < 0) x1 += MOD1;
        if (x2 < 0) x2 += MOD2;
        return {x1, x2};
    }
};

string s;
rabin_karp rk;
vector<int> dp;

int f(const int st) {
    int &ret = dp[st];
    if (ret != -1) return ret;
    const int en = sz(s) - st - 1;
    if (en < st) return ret = 0;

    ret = 1;

    for (int i = st; i <= (st + en) / 2; i++) {
        if (i >= sz(s) - i - 1) break;
        if (rk.get(st, i + 1) == rk.get(sz(s) - i - 1, en + 1)) {
            ret = max(ret, 2 + f(i + 1));
            break;
        }
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> s;

    rk.build(s);
    dp.resize(sz(s), -1);

    cout << f(0) << '\n';
}
