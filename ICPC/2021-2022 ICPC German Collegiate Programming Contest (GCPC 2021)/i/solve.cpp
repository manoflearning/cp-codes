#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<vector<vector<int>>> f(m, vector<vector<int>>(m, vector<int>(m)));
    vector<vector<vector<vector<int>>>> g(m, vector<vector<vector<int>>>(m, vector<vector<int>>(m)));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                cin >> f[i][j][k];
                f[i][j][k]--;
            }
            for (int k = 0; k < m; k++) {
                g[i][j][f[i][j][k]].push_back(k);
            }
        }
    }

    vector<int> s0(n);
    for (auto &i : s0) {
        cin >> i;
        i--;
    }

    bool ans = 0;

    for (int p = 0; p < m; p++) {
        for (int q = 0; q < m; q++) {
            vector<vector<vector<int>>> dp(n + 2, vector<vector<int>>(m, vector<int>(m, 0)));

            // base case
            dp[0][p][q] = 1;
            // inductive step
            for (int i = 0; i + 1 <= n; i++) {
                for (int j = 0; j < m; j++) {
                    for (int k = 0; k < m; k++) {
                        if (!dp[i][j][k]) continue;

                        for (int l : g[j][k][s0[i]]) dp[i + 1][k][l] = 1;
                    }
                }
            }

            ans |= dp[n][p][q];
        }
    }

    cout << (ans ? "YES" : "NO");
}
