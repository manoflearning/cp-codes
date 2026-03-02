#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int P = 10101;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<int> p(n);
    for (auto &i : p) cin >> i;

    sort(p.rbegin(), p.rend());

    int sum{};
    for (auto &i : p) sum += i;

    ll ans = 0;
    vector<vector<ll>> dp(n + 1, vector<ll>(n * P));
    // base case
    dp[0][0] = 1;
    // inductive step
    for (int i = 0; i + 1 <= n; i++) {
        for (int j = 0; j <= sum / 2; j++) {
            if (!dp[i][j]) continue;

            dp[i + 1][j] += dp[i][j];
            dp[i + 1][j + p[i]] += dp[i][j];

            if (j <= sum / 2 && sum / 2 < j + p[i]) ans += dp[i][j];
        }
    }

    cout << ans << '\n';
}
