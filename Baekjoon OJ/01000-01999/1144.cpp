#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

struct profile {
    static constexpr int W = 9;
    static constexpr int BITS = 3;
    static constexpr int MASK = (1 << BITS) - 1;

    array<int, W> a{};

    void normalize() {
        int nxt{1}, mapval[W + 2]{};
        for (int i = 0; i < W; i++) {
            int &x = a[i];
            if (!x) continue;
            if (!mapval[x]) mapval[x] = nxt++;
            x = mapval[x];
        }
    }
    ll encode() const {
        ll ret{};
        for (int i = 0; i < W; i++)
            ret |= ((ll)a[i] << (BITS * i));
        return ret;
    }
    static profile decode(ll x) {
        array<int, W> ret{};
        for (int i = 0; i < W; i++)
            ret[i] = ((x >> (BITS * i)) & MASK);
        return profile{ret};
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    for (auto &i : a) for (auto &j : i) cin >> j;

    unordered_map<ll, int> dp[9][9];

    // base case
    for (int bit = 0; bit < (1 << m); bit++) {
        profile p{};
        int cnt{}, sum{};
        for (int i = 0; i < m; i++) {
            if (bit & (1 << i)) {
                p.a[i] = cnt;
                sum += a[0][i];
            } else cnt++;
        }
        p.normalize();
        dp[0][m - 1][p.encode()] = sum;
    }

    // inductive step
    for (int y = 1; y < n; y++) {
        for (int x = 0; x < m; x++) {
            int prv_y = (x == 0 ? y - 1 : y);
            int prv_x = (x == 0 ? m - 1 : x - 1);
            
        }
    }
}
