#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 998'244'353;
constexpr int N = 303;

int n, a[N];
ll dp[N][N];

ll power(ll x, ll y) {
    if (!y) return 1;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // base case
    for (int i = 2; i <= n; i++) {
        dp[i][i] = 1;
        // if (i + 1 <= n) dp[i][i + 1] = (a[i] < a[i + 1] ? 2 : 1);
    }

    // inductive step
    for (int len = 2; len <= n; len++) {
        for (int l = 2; l + len - 1 <= n; l++) {
            int r = l + len - 1;

            int cnt = 0;
            for (int i = l; i <= r; i++) {
                if (a[l] < a[i]) cnt++;
                // else if (i != l) continue;
                if (i < r && a[i + 1] < a[l]) continue;

                ll lv = -1, rv = -1;
                if (i == l) lv = 1;
                else lv = dp[l + 1][i];
                if (i == r) rv = 1;
                else rv = dp[i + 1][r];

                dp[l][r] = (dp[l][r] + lv * rv % MOD * power(2, cnt)) % MOD;
            }
        }
    }

    // for (int len = 1; len <= n; len++) {
    //     for (int l = 2; l + len - 1 <= n; l++) {
    //         int r = l + len - 1;
    //         cout << "dp[" << l << "][" << r << "] = " << dp[l][r] << '\n';
    //     }
    // }

    cout << dp[2][n];
}