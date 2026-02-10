#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

void bt(int l, int r, vector<int> &ans, const vector<ll> &a, const vector<vector<ll>> &dp) {
    if (l == r) return;

    if (dp[l][r] == 1 + dp[l + 1][r]) {
        ans.push_back(l);
        bt(l + 1, r, ans, a, dp);
    } else if (dp[l][r] == 1 + dp[l][r - 1]) {
        ans.push_back(r - 1);
        bt(l, r - 1, ans, a, dp);
    } else if (
        r - l >= 2
        && dp[l][r] == dp[l + 1][r - 1]
        && (a[l] % a[r - 1] == 0 || a[r - 1] % a[l] == 0)) {
        bt(l + 1, r - 1, ans, a, dp);
    } else {
        for (int k = l + 1; k < r; k++) {
            if (dp[l][r] == dp[l][k] + dp[k][r]) {
                bt(l, k, ans, a, dp);
                bt(k, r, ans, a, dp);
                break;
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, INF));

    // base case
    for (int i = 0; i <= n; i++) dp[i][i] = 0;
    
    // inductive step
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            const int r = l + len;

            dp[l][r] = min(dp[l][r], 1 + dp[l + 1][r]);
            dp[l][r] = min(dp[l][r], 1 + dp[l][r - 1]);
            if (len >= 2 && (a[l] % a[r - 1] == 0 || a[r - 1] % a[l] == 0)) {
                dp[l][r] = min(dp[l][r], dp[l + 1][r - 1]);
            }

            for (int k = l + 1; k < r; k++) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r]);
            }
        }
    }

    vector<int> ans;
    bt(0, n, ans, a, dp);
    sort(all(ans));

    assert(dp[0][n] == sz(ans));

    cout << dp[0][n] << '\n';
    for (auto &i : ans) cout << i + 1 << ' ';
}
