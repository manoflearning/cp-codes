#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int f(int n, int m, string s, string t) {
    if (n == 1) return 1;
    if (n >= 2 && m == 1) return 2;
    if (s[0] != t[0] || s[n - 1] != t[m - 1]) return (n == 1 ? 1 : 2);

    vector<vector<int>> dp2(26, vector<int>(m, -1));
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = j + 1; k < m; k++) {
                if (i + 'a' == t[k]) {
                    dp2[i][j] = k;
                    break;
                }
            }
        }
    }

    int ret = min(n, m + 1);

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(m, INF)));

    // base case
    dp[0][0][0] = 1;
    for (int i = 1; i < n - 1; i++) {
        bool yes = 0;
        for (int j = 0; j < m; j++) {
            if (s[i] == t[j]) { dp[i][i][j] = 2; yes = 1; break; }
        }
        if (!yes) ret = min(ret, 3);
    }
    dp[n - 1][n - 1][m - 1] = 2;

    // inductive step
    for (int i = 0; i + 1 < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k < m; k++) {
                if (dp[i][j][k] == INF) continue;

                dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);

                const int l = dp2[s[i + 1] - 'a'][k];
                if (i == j) {
                    if (l == k + 1) {
                        dp[i + 1][i + 1][l] = min(dp[i + 1][i + 1][l], dp[i][j][k] + 1);
                    } else {
                        ret = min(ret, dp[i][j][k] + 1 + (i + 2 < n));
                    }
                } else {
                    if (l != -1) {
                        dp[i + 1][i + 1][l] = min(dp[i + 1][i + 1][l], dp[i][j][k] + 2);
                    } else {
                        ret = min(ret, dp[i][j][k] + 2 + (i + 2 < n));
                    }
                }
                
            }
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    const int ans = f(n, m, s, t);
    cout << ans << '\n';
}
