#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll MOD = 1e5;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll N; cin >> N;
    string S; cin >> S;

    vector<vector<ll>> dp(N, vector<ll>(N, 0));
    vector<vector<ll>> dp_only(N, vector<ll>(N, 0));
    vector<vector<bool>> dp_modified(N, vector<bool>(N, false));

    bool over_mod = 0;

    for (ll len = 2; len <= N; len += 2) {
        for (ll s = 0; s < N; s++) { // dp[s][e]
            ll e = s + len - 1;
            if (e >= N) break;

            for (ll mid = s + 1; mid + 1 <= e; mid += 2) {
                dp[s][e] += dp_only[s][mid] * dp[mid + 1][e];
                if (dp_modified[s][mid] && dp_modified[mid + 1][e]) dp_modified[s][e] = 1;
                if (MOD <= dp[s][e]) {
                    over_mod = 1;
                    dp[s][e] %= MOD;
                }
            }

            ll flag = 0;
            if (S[s] == '?' && S[e] == '?') flag = 3;
            else if (S[s] == '?' && (S[e] == ')' || S[e] == '}' || S[e] == ']')) flag = 1;
            else if ((S[s] == '(' || S[s] == '{' || S[s] == '[') && S[e] == '?') flag = 1;
            else if (S[s] == '(' && S[e] == ')') flag = 1;
            else if (S[s] == '{' && S[e] == '}') flag = 1;
            else if (S[s] == '[' && S[e] == ']') flag = 1;

            if (len == 2) {
                dp_only[s][e] = flag;
                if (flag > 0) dp_modified[s][e] = 1;
            }
            else {
                dp_only[s][e] = flag * dp[s + 1][e - 1];
                if (flag > 0 && dp_modified[s + 1][e - 1]) dp_modified[s][e] = 1;
                if (MOD <= dp_only[s][e]) {
                    over_mod = 1;
                    dp_only[s][e] %= MOD;
                }
            }

            dp[s][e] += dp_only[s][e];
            if (MOD <= dp[s][e]) {
                over_mod = 1;
                dp[s][e] %= MOD;
            }
        }
    }

    string ans = to_string(dp[0][N - 1]);

    if (over_mod && dp_modified[0][N - 1]) {
        for (int i = 0; i < 5 - sz(ans); i++) cout << '0';
    }
    cout << ans;

    return 0;
}