#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

string dp[111];

string ll_to_binary_string(ll x) {
    string ret;
    bool is_started = 0;
    for (int i = 60; i >= 0; i--) {
        if ((1ll << i) & x) {
            is_started = 1;
            ret += '1';
        }
        else if (is_started) ret += '0';
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    dp[1] = "1";
    int top;
    for (top = 2; ; top++) {
        ll cnt0 = 0, cnt1 = 0;
        for (int j = 0; j < sz(dp[top - 1]); j++) {
            if (dp[top - 1][j] == '1') {
                if (cnt0) {
                    dp[top] += ll_to_binary_string(cnt0);
                    dp[top] += '0';
                    cnt0 = 0;
                }
                cnt1++;
            }
            if (dp[top - 1][j] == '0') {
                if (cnt1) {
                    dp[top] += ll_to_binary_string(cnt1);
                    dp[top] += '1';
                    cnt1 = 0;
                }
                cnt0++;
            }
        }
        if (cnt0) {
            dp[top] += ll_to_binary_string(cnt0);
            dp[top] += '0';
        }
        if (cnt1) {
            dp[top] += ll_to_binary_string(cnt1);
            dp[top] += '1';
        }

        if (sz(dp[top - 1]) > (int)2e6 && sz(dp[top]) > (int)2e6) break;
    }

    for (int i = 1; i <= top; i++) {
        reverse(dp[i].begin(), dp[i].end());
    }

    int tc; cin >> tc;
    while (tc--) {
        ll n; int m;
        cin >> n >> m;
        if (n <= top) {
            if (m < sz(dp[n])) cout << dp[n][m] << '\n';
            else cout << 0 << '\n';
        }
        else {
            if (n % 2 == top % 2) cout << dp[top][m] << '\n';
            else cout << dp[top - 1][m] << '\n';
        }
    }
}