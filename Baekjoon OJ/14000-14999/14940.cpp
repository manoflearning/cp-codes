#include <bits/stdc++.h>
using namespace std;

const int dy[] = { 1, 0, -1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int n, m;
int a[1010][1010], dist[1010][1010];
int sty = -1, stx = -1;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dist, -1, sizeof(dist));

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 2) sty = i, stx = j;
            if (a[i][j] == 0) dist[i][j] = 0;
        }
    }

    queue<pair<int, int>> q;
    q.push({ sty, stx });
    dist[sty][stx] = 0;
    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
            if (dist[ny][nx] != -1) continue;
            if (a[ny][nx] == 0) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push({ ny, nx });
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
}