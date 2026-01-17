#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int MOD = 998'244'353;

int n;
string s;

vector<vector<vector<ll>>> dp1;
// vector<ll> suf;
vector<vector<vector<vector<ll>>>> dp2;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> s;

        ll ans = 0;

        dp1.assign(n, vector<vector<ll>>(n + 1, vector<ll>(n + 1, 0)));
        {
            dp1[0][0][0] = 1;
            dp1[0][s[0] == '('][s[0] == '('] = 1;

            for (int i = 1; i < n; i++) {
                for (int l = 0; l <= n; l++) {
                    for (int up = 0; up <= n; up++) {
                        dp1[i][l][up] += dp1[i - 1][l][up];

                        if (s[i] == '(' && l > 0 && up > 0) dp1[i][l][up] += dp1[i - 1][l - 1][up - 1];
                        if (s[i] == ')' && l > 0 && up < n) dp1[i][l][up] += dp1[i - 1][l - 1][up + 1];

                        dp1[i][l][up] %= MOD;
                    }
                }
            }
        }

        for (int l = 2; l <= n; l += 2) {
            ans += (l - 2) * dp1[n - 1][l][0] % MOD;
            ans %= MOD;
        }

        dp2.assign(n, vector<vector<vector<ll>>>(n + 1, vector<vector<ll>>(n + 1, vector<ll>(4, 0))));

        {
            dp2[0][0][0][0] = 1;
            dp2[0][s[0] == '('][s[0] == '('][0] = 1;

            for (int i = 1; i < n; i++) {
                for (int l = 0; l <= n; l++) {
                    for (int up = 0; up <= n; up++) {
                        for (int d = 0; d < 4; d++) {
                            dp2[i][l][up][d] += dp2[i - 1][l][up][d];

                            if (d & 1) {
                                if (s[i] == ')' && l > 0 && up < n) {
                                    dp2[i][l][up][d] += dp2[i - 1][l - 1][up + 1][d - 1];
                                    dp2[i][l][up][d] += dp2[i - 1][l - 1][up + 1][d];
                                }
                            } else {
                                if (s[i] == '(' && d == 0 && l > 0 && up > 0) {
                                    dp2[i][l][up][d] += dp2[i - 1][l - 1][up - 1][d];
                                }
                                if (s[i] == '(' && d == 2 && l > 0 && up > 0) {
                                    dp2[i][l][up][d] += dp2[i - 1][l - 1][up - 1][d - 1];
                                }
                            }

                            dp2[i][l][up][d] %= MOD;
                        }
                    }
                }
            }
        }

        for (int l = 2; l <= n; l += 2) {
            ans -= (l - 2) * dp2[n - 1][l][0][1] % MOD;
            ans -= (l - 2) * dp2[n - 1][l][0][3] % MOD;
            ans = (ans % MOD + MOD) % MOD;
        }

        cout << ans << '\n';
    }
}
