#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int dy[] = {0, 1, 0, -1};
constexpr int dx[] = {1, 0, -1, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<vector<int>> a(n, vector<int>(n));
        for (auto &i : a) for (auto &j : i) cin >> j;

        int ans = 0;
        vector<vector<bool>> vis(n, vector<bool>(n));
        for (int y = 1; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (vis[y - 1][x]) continue;
                for (int d = 0; d < 4; d++) {
                    const int ny = y + dy[d], nx = x + dx[d];
                    if (ny < 0 || n <= ny || nx < 0 || n <= nx) continue;
                    vis[ny][nx] = !vis[ny][nx];
                }
                ans ^= a[y][x];
            }
        }

        cout << ans << '\n';
    }
}
