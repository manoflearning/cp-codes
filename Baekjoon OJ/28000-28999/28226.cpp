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

constexpr ll INF = 1e18;

// what: normalized rational type with exact arithmetic and comparisons.
// time: O(log max(|n|,|d|)) per op; memory: O(1)
// constraint: denominator != 0; results must fit in 64-bit.
// usage: fraction a(1, 3), b(2, 5); fraction c = a + b;
struct fraction {
    ll n, d;

    fraction(ll n_ = 0, ll d_ = 1) { set(n_, d_); }
    void set(ll n_, ll d_) {
        // goal: normalize sign + reduce
        n = n_;
        d = d_;
    }

    bool operator<(const fraction &rhs) const {
        return (__int128)n * rhs.d < (__int128)rhs.n * d;
    }
    bool operator<=(const fraction &rhs) const { return !(rhs < *this); }
};

int n;
vector<ll> t, p;
vector<vector<int>> jumps;
ll delta;
vector<ll> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    t.assign(n, -1);
    p.assign(n, -1);
    for (int i = 0; i < n; i++)
        cin >> t[i] >> p[i];
    jumps.assign(n, vector<int>());
    cin >> delta;

    for (int i = 0; i < n; i++) {
        fraction lb{-INF, 1}, ub{INF, 1};

        for (int j = i + 1; j < n; j++) {
            fraction sl{p[j] - p[i], t[j] - t[i]};
            if (lb <= sl && sl <= ub) {
                jumps[i].push_back(j);
            }

            lb = max(lb, fraction{p[j] - delta - p[i], t[j] - t[i]});
            ub = min(ub, fraction{p[j] + delta - p[i], t[j] - t[i]});
        }
    }

    dp.assign(n, INF);
    // base case
    dp[n - 1] = 1;
    // inductive step
    for (int i = n - 2; i >= 0; i--) {
        for (int j : jumps[i]) {
            dp[i] = min(dp[i], 1 + dp[j]);
        }
    }
    cout << dp[0];
}
