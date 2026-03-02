#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int D = 60;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; ll k;
    string s;
    cin >> n >> k >> s;

    vector<vector<int>> dp(D, vector<int>(n));

    for (int i = 0, j = 0; j < n; i = (i + 2) % n, j++) {
        dp[0][j] = i;
    }

    vector<int> fuck(n);
    iota(all(fuck), 0);

    if (k & 1) fuck = dp[0];

    for (int d = 0; d + 1 < D; d++) {
        for (int i = 0; i < n; i++) {
            dp[d + 1][i] = dp[d][dp[d][i]];
        }

        if ((1ll << (d + 1)) & k) {
            vector<int> tmp(n);
            for (int i = 0; i < n; i++) {
                tmp[i] = dp[d + 1][fuck[i]];
            }
            fuck.swap(tmp);
        }
    }

    string ans(n, '.');
    for (int i = 0; i < n; i++) {
        ans[i] = s[fuck[i]];
    }
    cout << ans;
}
