#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int dy[] = { 1, 1, -1, -1, 1, 0, -1, 0 };
const int dx[] = { -1, 1, 1, -1, 0, 1, 0, -1 };

bool is_valid(const vector<string>& ans) {
    vector<vector<bool>> vis(sz(ans), vector<bool>(sz(ans[0])));

    queue<pair<int, int>> qu;
    vis[0][0] = 1;
    qu.push({ 0, 0 });
    
    while (!qu.empty()) {
        auto [y, x] = qu.front();
        qu.pop();

        int deg = 0;
        for (int d = 0; d < 8; d++) {
            int ny = dy[d] + y, nx = dx[d] + x;
            if (ny < 0 || sz(ans) <= ny || nx < 0 || sz(ans[0]) <= nx) continue;
            if (ans[ny][nx] == '*') deg++;
        }

        if (deg > 0) continue;

        for (int d = 0; d < 8; d++) {
            int ny = dy[d] + y, nx = dx[d] + x;
            if (ny < 0 || sz(ans) <= ny || nx < 0 || sz(ans[0]) <= nx) continue;
            if (ans[ny][nx] == '*') continue;
            if (vis[ny][nx]) continue;
            vis[ny][nx] = 1;
            qu.push({ ny, nx });
        }
    }

    for (int i = 0; i < sz(ans); i++) {
        for (int j = 0; j < sz(ans[0]); j++) {
            if (vis[i][j] ^ (ans[i][j] != '*')) return 0;
        }
    }
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ":\n";

        int r, c, w;
        cin >> r >> c >> w;

        if (w + 1 == r * c) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (i == 0 && j == 0) cout << 'c';
                    else cout << '*';
                }
                cout << '\n';
            }
        }
        else if (w == r * c) cout << "Impossible\n";
        else if (r == 1 && c == 1) cout << "c\n";
        else if (r == 1 || c == 1) {
            string ans;
            ans += 'c';
            ans += string(max(r, c) - 1 - w, '.');
            ans += string(w, '*');
            if (r == 1) cout << ans << '\n';
            else {
                for (auto& i : ans) cout << i << '\n';
            }
        }
        else {
            vector<string> ans(r, string(c, '.'));
            ans[0][0] = 'c';
            
            // for (int d = max(r - 1, c - 1); d >= 0; d--) {
            //     for (int i = d; i >= 0; i--) {
            //         int y = d, x = i;
            //         if (w > 0 && 0 <= y && y < r && 0 <= x && x < c && ans[y][x] == '.') {
            //             ans[y][x] = '*';
            //             w--;
            //         }
            //         y = i, x = d;
            //         if (w > 0 && 0 <= y && y < r && 0 <= x && x < c && ans[y][x] == '.') {
            //             ans[y][x] = '*';
            //             w--;
            //         }
            //     }
            // }

            for (int i = r - 1; i >= 2; i--) {
                for (int j = c - 1; j >= 0; j--) {
                    if (w == 0) break;
                    ans[i][j] = '*';
                    w--;
                }
            }

            for (int j = c - 1; j >= 0; j--) {
                if (w & 1) {
                    if (2 < r && 2 < c) {
                        ans[2][0] = '.';
                        ans[2][1] = '.';
                        ans[2][2] = '.';
                        w += 3;
                    }
                }
                if (w > 0) { ans[1][j] = '*'; w--; }
                if (w > 0) { ans[0][j] = '*'; w--; }
            }

            if (w == 0 && is_valid(ans)) for (auto& i : ans) cout << i << '\n';
            else cout << "Impossible\n";
        }
    }
}