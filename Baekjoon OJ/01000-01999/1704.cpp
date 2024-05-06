#include <bits/stdc++.h>
using namespace std;

const int dy[] = { 0, 0, 0, 1, -1 };
const int dx[] = { 0, 1, -1, 0, 0 };

int n, m;
vector<vector<int>> a;

vector<vector<int>> ans;
int ans_cnt = 1e9 + 7;

void input() {
    cin >> n >> m;
    a.resize(n, vector<int>(m));
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++) cin >> a[y][x];
}

void solve() {
    ans.resize(n, vector<int>(m, 2));

    for (int bit = 0; bit < (1 << m); bit++) {
        vector<vector<int>> b = a;
        vector<vector<int>> res(n, vector<int>(m));
        int res_cnt = 0;

        // first row
        for (int x = 0; x < m; x++) {
            if (!(bit & (1 << x))) continue;
            for (int d = 0; d < 5; d++) {
                int ny = 0 + dy[d], nx = x + dx[d];
                if (ny < 0 || nx < 0 || n <= ny || m <= nx) continue;
                b[ny][nx] = !b[ny][nx];
            }
            res[0][x] = 1;
            res_cnt++;
        }

        // y(>=1) th row
        for (int y = 1; y < n; y++) {
            for (int x = 0; x < m; x++) {
                if (!b[y - 1][x]) continue;
                for (int d = 0; d < 5; d++) {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (ny < 0 || nx < 0 || n <= ny || m <= nx) continue;
                    b[ny][nx] = !b[ny][nx];
                }
                res[y][x] = 1;
                res_cnt++;
            }
        }

        // is it valid?
        bool is_valid = 1;
        for (int x = 0; x < m; x++) {
            if (b[n - 1][x]) is_valid = 0;
        }

        if (is_valid) {
            if (res_cnt < ans_cnt) ans = res, ans_cnt = res_cnt;
            else if (res_cnt == ans_cnt) ans = min(ans, res), ans_cnt = res_cnt;
        }
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
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    output();
}