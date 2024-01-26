#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 212;

string s, dp[MAXN][MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;

    for (int i = 0; i < sz(s); i++) dp[i][i] = s[i];

    for (int len = 2; len <= sz(s); len++) {
        for (int l = 0, r = len - 1; r < sz(s); l++, r++) {
            for (int i = l; i <= r; i++) dp[l][r] += s[i]; // O(n^3)

            for (int d = 1; d <= len; d++) { // O(n^3 sqrt(n))
                if (len % d) continue;
                if (len / d >= 10) continue;

                bool isValid = 1;
                for (int i = l; i + d <= r; i++) {
                    if (s[i] != s[i + d]) { isValid = 0; break; }
                }
                if (isValid) {
                    string tmp;
                    tmp += '0' + len / d;
                    tmp += '(';
                    tmp += dp[l][l + d - 1];
                    tmp += ')';
                    if (sz(tmp) < sz(dp[l][r])) dp[l][r] = tmp;
                }
            }

            for (int i = l; i + 1 <= r; i++) { // O(n^4)
                if (sz(dp[l][i]) + sz(dp[i + 1][r]) < sz(dp[l][r])) {
                    dp[l][r] = dp[l][i] + dp[i + 1][r];
                }
            }

            // cout << l << ' ' << r << ' ' << dp[l][r] << '\n';
        }
    }

    cout << dp[0][sz(s) - 1];
}