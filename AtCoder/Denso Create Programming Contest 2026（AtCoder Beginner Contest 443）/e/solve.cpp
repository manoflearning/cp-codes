#pragma GCC optimize ("O3")
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

    int tc; cin >> tc;
    while (tc--) {
        int n, c;
        cin >> n >> c;

        vector<string> a(n);
        for (auto &i : a) cin >> i;

        vector<vector<int>> dp(n, vector<int>(n));
        vector<vector<int>> suf(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) suf[i][j] = a[i][j] == '#';
        for (int j = 0; j < n; j++)
            for (int i = n - 2; i >= 0; i--) suf[i][j] += suf[i + 1][j];

        // base case
        dp[n - 1][c - 1] = 3;

        // inductive step
        for (int y = n - 1; y >= 1; y--) {
            for (int x = 0; x < n; x++) {
                if (!dp[y][x]) continue;

                const int ny = y - 1;
                for (int dx = -1; dx <= 1; dx++) {
                    const int nx = x + dx;
                    if (nx < 0 || n <= nx) continue;

                    if ((dp[y][x] & 2) && x == nx) dp[ny][nx] |= dp[y][x];

                    if (a[ny][nx] == '.') {
                        dp[ny][nx] |= 1;
                        dp[ny][nx] |= (!suf[y][nx] ? 2 : 0);
                    } else {
                        dp[ny][nx] |= (!suf[y][nx] ? 3 : 0);
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) cout << (dp[0][i] ? 1 : 0);
        cout << '\n';
    }

    return 0;
}
