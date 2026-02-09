#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    string s; cin >> s;

    vector<vector<int>> dp(sz(s) + 1, vector<int>(sz(s) + 1, INF));
    vector<vector<pii>> opt(sz(s) + 1, vector<pii>(sz(s) + 1, {-1, -1}));

    for (int len = 0; len <= sz(s); len++) {
        for (int l = 0; l + len <= sz(s); l++) {
            const int r = l + len;

            dp[l][r] = len;
            opt[l][r] = {0, 0};

            for (int i = l + 1; i < r; i++) {
                const int res = dp[l][i] + dp[i][r];
                if (dp[l][r] > res) {
                    dp[l][r] = res;
                    opt[l][r] = {0, i};
                }
            }

            for (int d = 1; d <= len; d++) {
                if (len % d) continue;
                if (len / d >= 10) continue;

                const string p{s.begin() + l, s.begin() + l + d};

                bool yes = 1;
                for (int i = l + d; i + d <= r; i += d) {
                    const string q{s.begin() + i, s.begin() + i + d};
                    yes &= p == q;
                }

                if (!yes) continue;

                const int res = 3 + dp[l][l + d];
                if (dp[l][r] > res) {
                    dp[l][r] = res;
                    opt[l][r] = {1, d};
                }
            }
        }
    }

    string ans;

    function<void(int, int)> dfs = [&](int l, int r) -> void {
        if (opt[l][r] == pii{0, 0}) {
            ans += string{s.begin() + l, s.begin() + r};
        } else if (opt[l][r].first == 0) {
            dfs(l, opt[l][r].second);
            dfs(opt[l][r].second, r);
        } else {
            const int d = opt[l][r].second;
            const int cnt = (r - l) / d;

            ans += to_string(cnt);
            ans += "(";
            dfs(l, l + d);
            ans += ")";
        }
    };

    dfs(0, sz(s));

    cout << ans;
}
