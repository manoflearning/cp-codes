#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

ll dp[55][55] = { 0, };

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<string> a(n);
    for (auto& i : a) cin >> i;

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";

        string t; cin >> t;

        for (int i = 0; i < 55; i++) {
            for (int j = 0; j < 55; j++) {
                dp[i][j] = INF;
            }
        }

        for (int i = 0; i < sz(t); i++) {
            for (const auto& s : a) {
                int j = i - sz(s) + 1;
                if (j < 0) continue;

                ll cnt = 0;
                int prv = sz(t), st = sz(t) + 100;
                for (int k = j; k <= i; k++) {
                    if (t[k] == s[k - j]) continue;

                    if (prv != sz(t) && !(prv + 5 <= k)) {
                        cnt = INF;
                        // break;
                    }
                    cnt++;
                    prv = k;
                    if (st == sz(t) + 100) st = k;
                }

                // base case
                if (j == 0) {
                    dp[i][prv] = min(dp[i][prv], cnt);
                }
                // inductive step
                else {
                    for (int k = 0; k <= min(j - 1, st - 5); k++) {
                        dp[i][prv] = min(dp[i][prv], cnt + dp[j - 1][k]);
                    }
                    dp[i][prv] = min(dp[i][prv], cnt + dp[j - 1][sz(t)]);
                }
            }
        }

        ll ans = dp[sz(t) - 1][sz(t)];
        for (int i = 0; i < 55; i++)
            ans = min(ans, dp[sz(t) - 1][i]);

        assert(ans != INF);
        cout << ans << '\n';
    }
}