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

constexpr int MOD = 998'244'353;
constexpr int M = 3030;

ll gcd_(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
ll lcm_(ll x, ll y) {
    return x * y / gcd_(x, y);
}

// int lcm[M][M];
vector<int> nxt[M];

ld naive_ld(const vector<int> &a) {
    ld ret = 0;
    for (int i = 0; i < sz(a); i++) {
        ret += (ld)1 / lcm_(a[i], a[(i + 1) % sz(a)]);
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    // vector<int> a = {1, 2, 4, 6, 12};
    // cout << naive_ld(a) << '\n';

    for (int i = 1; i < M; i++) {
        // nxt[i].push_back(i + 1);
        for (int j = i + 1; j < M; j++) {
            // if (2 * i < j) break;
            if (gcd_(i, j) >= j - i) {
                nxt[i].push_back(j);
            }
        }
    }

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        if (a[0] > 1) {
            cout << 0 << '\n';
            continue;
        }

        vector<vector<ll>> dp(n, vector<ll>(m + 1));
        
        // base case
        dp[0][1] = 1;

        // inductive step
        for (int i = 0; i + 1 < n; i++) {
            if (a[i]) {
                for (int k : nxt[a[i]]) {
                    if (m < k) break;
                    // cout << i << ' ' << a[i] << ' ' << k << '\n';
                    dp[i + 1][k] = (dp[i + 1][k] + dp[i][a[i]]) % MOD;
                }
            } else {
                for (int j = 1; j <= m; j++) {
                    if (!dp[i][j]) continue;
                    for (int k : nxt[j]) {
                        if (m < k) break;
                        // cout << i << ' ' << j << ' ' << k << '\n';
                        dp[i + 1][k] = (dp[i + 1][k] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        ll ans = 0;
        if (a[n - 1]) {
            ans = dp[n - 1][a[n - 1]];
        } else {
            for (int j = 1; j <= m; j++) {
                ans = (ans + dp[n - 1][j]) % MOD;
                // cout << j << ' ' << dp[n - 1][j] << '\n';
            }
        }

        cout << ans << '\n';
    }
}
