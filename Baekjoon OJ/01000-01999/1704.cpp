#include <bits/stdc++.h>
using namespace std;

const int dy[] = { 0, 0, 0, 1, -1 };
const int dx[] = { 0, 1, -1, 0, 0 };

int n, m;
vector<vector<int>> a;
vector<vector<int>> ans;

void input() {
    cin >> n >> m;
    a.resize(n, vector<int>(m));
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++) cin >> a[y][x];
}

void solve() {
    ans.resize(n, vector<int>(m, 2));

    for (int bit = 0; bit < (1 << n); bit++) {
        vector<vector<int>> b = a;
        vector<vector<int>> res(n, vector<int>(m));

        // first row
        for (int x = 0; x < m; x++) {
            if (!(bit & (1 << x))) continue;
            int y = 0;
            for (int d = 0; d < 5; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || nx < 0 || n <= ny || m <= nx) continue;
                b[ny][nx] = !b[ny][nx];
            }
            res[y][x] = 1;
        }

        // x(>=2) th row
        for (int y = 1; y < n; y++) {
            for (int x = 0; x < m; x++) {
                if (!b[y - 1][x]) continue;
                for (int d = 0; d < 5; d++) {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (ny < 0 || nx < 0 || n <= ny || m <= nx) continue;
                    b[ny][nx] = !b[ny][nx];
                }
                res[y][x] = 1;
            }
        }

        // is it valid?
        bool is_valid = 1;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                if (b[y][x]) is_valid = 0;
            }
        }

        if (is_valid) ans = min(ans, res);
    }
}

void output() {
    if (ans[0][0] == 2) cout << "IMPOSSIBLE";
    else {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                cout << ans[y][x] << ' ';
            }
            cout << '\n';
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    output();
}