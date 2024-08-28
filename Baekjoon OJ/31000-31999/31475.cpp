#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int dy[] = { 1, -1, 0, 0 };
const int dx[] = { 0, 0, 1, -1 };

int n, m;
string s;
int dist[2020][2020];

void bfs(int sty, int stx, int stdir) {
    memset(dist, -1, sizeof(dist));

    queue<tuple<int, int, int>> qu;
    dist[sty][stx] = 1;
    qu.push({ sty, stx, stdir });

    while (!qu.empty()) {
        auto [y, x, dir] = qu.front();
        qu.pop();

        int ny = y + dy[dir], nx = x + dx[dir];
        if (0 <= ny && ny < n && 0 <= nx && nx < m && dist[ny][nx] == -1) {
            dist[ny][nx] = dist[y][x] + 1;
            qu.push({ ny, nx, dir });
        }
        else {
            for (int d = 0; d < 4; d++) {
                ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
                if (dist[ny][nx] != -1) continue;
                dist[ny][nx] = dist[y][x] + 1;
                qu.push({ ny, nx, d });
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> s;

    if (s == "U") bfs(0, m / 2, 0);
    else if (s == "D") bfs(n - 1, m / 2, 1);
    else if (s == "L") bfs(n / 2, 0, 2);
    else if (s == "R") bfs(n / 2, m - 1, 3);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
}
