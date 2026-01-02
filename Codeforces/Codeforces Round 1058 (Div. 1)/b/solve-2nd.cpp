#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<char>> a(n);
        for (auto &i : a) {
            string s; cin >> s;
            i.resize(m);
            for (int j = 0; j < m; j++) {
                i[j] = s[j];
            }
        }

        bool is_fliped = 0;
        if (n > m) {
            is_fliped = 1;
            vector<vector<char>> tmp(m, vector<char>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    tmp[j][i] = a[i][j];
                }
            }
            a = tmp;
            swap(n, m);
        }

        vector<vector<int>> ans(n, vector<int>(m));

        vector<vector<int>> l(n, vector<int>(n, -1));
        vector<vector<int>> r(n, vector<int>(n, -1));

        for (int x = 0; x < m; x++) {
            vector<vector<int>> dp(n, vector<int>(n, INF));

            for (int y1 = 0; y1 < n; y1++) {
                for (int y2 = y1 + 1; y2 < n; y2++) {
                    if (x <= r[y1][y2]) {
                        dp[y1][y2] = min(dp[y1][y2], (y2 - y1 + 1) * (r[y1][y2] - l[y1][y2] + 1));
                    }

                    if (a[y1][x] == '1' && a[y2][x] == '1') {
                        l[y1][y2] = x;
                        int nxt = x + 1;
                        while (nxt < m && !(a[y1][nxt] == '1' && a[y2][nxt] == '1')) nxt++;
                        if (nxt < m) r[y1][y2] = nxt;
                        else r[y1][y2] = -1;

                        if (r[y1][y2] != -1) {
                            dp[y1][y2] = min(dp[y1][y2], (y2 - y1 + 1) * (r[y1][y2] - l[y1][y2] + 1));
                        }
                    }
                }
            }

            for (int l = n - 1; l >= 1; l--) {
                for (int y1 = 0, y2 = l - 1; y2 < n; y1++, y2++) {
                    if (y2 + 1 < n) dp[y1][y2] = min(dp[y1][y2], dp[y1][y2 + 1]);
                    if (0 <= y1 - 1) dp[y1][y2] = min(dp[y1][y2], dp[y1 - 1][y2]);
                }
            }

            for (int y = 0; y < n; y++) {
                ans[y][x] = (dp[y][y] == INF ? 0 : dp[y][y]);
            }
        }

        if (is_fliped) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << ans[j][i] << ' ';
                }
                cout << '\n';
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ans[i][j] << ' ';
                }
                cout << '\n';
            }
        }
    }
}