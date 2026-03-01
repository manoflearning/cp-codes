#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n;
    string s;
    cin >> n >> s;

    vector<array<ll, 3>> dp(n, array<ll, 3>{});
    ll pow3{};

    // base case
    dp[0] = {0, 1, s[0] - '0'};
    pow3 = 1;

    // inductive step
    for (int i = 0; i + 1 < n; i++) {
        const ll x = s[i + 1] - '0';

        const auto [a, b, c] = dp[i];
        auto &[na, nb, nc] = dp[i + 1];

        // concat
        na = (na + a) % MOD;
        nb = (nb + b) % MOD;
        nc = (nc + c * 10 + x * b) % MOD;

        // '+'
        na = (na + a + c) % MOD;
        nb = (nb + pow3) % MOD;
        nc = (nc + x * pow3) % MOD;

        // '*'
        na = (na + a) % MOD;
        nb = (nb + c) % MOD;
        nc = (nc + x * c) % MOD;

        pow3 = 3 * pow3 % MOD;
    }

    const ll ans = (dp[n - 1][0] + dp[n - 1][2]) % MOD;
    cout << ans << '\n';
}
