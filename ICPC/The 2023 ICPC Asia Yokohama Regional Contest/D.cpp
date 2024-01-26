// dp[i][j] = i에서 j까지 압축했을 때 최소 길이
// dp[1][n], dp[i][j] = min_len(dp[i][k] + dp[k + 1][j], divisor)
// O(n^3 sqrt(n))

#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 212;
const int INF = 1e9 + 7;

string s;
string dp[MAXN][MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;
    
    for (int i = 0; i < sz(s); i++) {
        dp[i][i] = s[i];
    }

    for (int len = 2; len <= sz(s); len++) {
        for (int l = 0, r = len - 1; r < sz(s); l++, r++) {
            for (int i = l; i <= r; i++) dp[l][r] += s[i];

            for (int div = 1; div <= len; div++) {
                if (len % div) continue;
                if (len / div >= 10) continue;

                bool isValid = 1;
                for (int i = l; i + div <= r; i++) {
                    if (s[i] != s[i + div]) {
                        isValid = 0;
                        break;
                    }
                }

                if (isValid) {
                    int resLen = 3 + sz(dp[l][l + div - 1]);
                    if (resLen < sz(dp[l][r])) {
                        string res;
                        res += to_string(len / div);
                        res += '(';
                        res += dp[l][l + div - 1];
                        res += ')';
                        dp[l][r] = res;
                    }
                }
            }

            int p = -1, pLen = sz(dp[l][r]);
            for (int i = l; i + 1 <= r; i++) {
                if (dp[l][r].empty() || sz(dp[l][i]) + sz(dp[i + 1][r]) < pLen) {
                    p = i;
                    pLen = sz(dp[l][i]) + sz(dp[i + 1][r]);
                }
            }
            if (p != -1) dp[l][r] = dp[l][p] + dp[p + 1][r];
        }
    }

    cout << dp[0][sz(s) - 1];
}