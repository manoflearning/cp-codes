#include <bits/stdc++.h>
using namespace std;

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, -1, 0, 1 };

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto& i : a) cin >> i;

    int sy = -1, sx = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'I') sy = i, sx = j;
        }
    }

    int ans = 0;
    
    vector<vector<bool>> vi(n, vector<bool>(m));
    queue<pair<int, int>> q;
    q.push({ sy, sx });
    vi[sy][sx] = 1;

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        if (a[y][x] == 'P') ans++;

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (vi[ny][nx]) continue;
            if (a[ny][nx] == 'X') continue;
            q.push({ ny, nx });
            vi[ny][nx] = 1;
        }
    }

    if (ans) cout << ans;
    else cout << "TT";
}