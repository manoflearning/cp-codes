#pragma GCC optimize ("Ofast, unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 998'244'353;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<ll> p(n);
    for (auto &i : p) cin >> i;

    vector<ll> dp(202020);
    dp[101010] = 1;

    for (const int i : p) {
        vector<ll> nxt(202020);
        for (int j = 0; j < 202020; j++) {
            if (!dp[j]) continue;
            nxt[j - i] = (nxt[j - i] + dp[j]) % MOD;
            nxt[j + i] = (nxt[j + i] + dp[j]) % MOD;
        }
        dp = std::move(nxt);
    }

    const ll ans = ((dp[101010] * dp[101010] - 2 * dp[101010]) % MOD + MOD) % MOD;
    cout << ans << '\n';
}
