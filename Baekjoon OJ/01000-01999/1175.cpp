#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int dy[] = { 1, 0, -1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int n, m;
int sy, sx, ey1 = -1, ex1, ey2, ex2;
vector<string> a;
int dist[55][55][4][4];

void bfs() {
    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 55; j++) {
            for (int k = 0; k < 4; k++) {
                dist[i][j][k][0] = dist[i][j][k][1] = INF;
                dist[i][j][k][2] = dist[i][j][k][3] = INF;
            }
        }
    }

    struct Node {
        int y, x, d, bit;
    };

    queue<Node> q;
    q.push({ sy, sx, 0, 0 });
    q.push({ sy, sx, 1, 0 });
    q.push({ sy, sx, 2, 0 });
    q.push({ sy, sx, 3, 0 });
    dist[sy][sx][0][0] = 0;
    dist[sy][sx][1][0] = 0;
    dist[sy][sx][2][0] = 0;
    dist[sy][sx][3][0] = 0;

    while (!q.empty()) {
        int y = q.front().y, x = q.front().x;
        int d = q.front().d, bit = q.front().bit;
        q.pop();

        for (int i = 0; i < 4; i++) {
            if (d == i) continue;
            
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (a[ny][nx] == '#') continue;
            
            int nbit = bit;
            if (ny == ey1 && nx == ex1) nbit |= 1;
            if (ny == ey2 && nx == ex2) nbit |= 2;

            if (dist[ny][nx][i][nbit] != INF) continue;

            q.push({ ny, nx, i, nbit });
            dist[ny][nx][i][nbit] = dist[y][x][d][bit] + 1;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') sy = i, sx = j;
            if (a[i][j] == 'C') {
                if (ey1 == -1) ey1 = i, ex1 = j;
                else ey2 = i, ex2 = j;
            }
        }
    }

    bfs();

    int ans = INF;

    ans = min(ans, dist[ey1][ex1][0][3]);
    ans = min(ans, dist[ey1][ex1][1][3]);
    ans = min(ans, dist[ey1][ex1][2][3]);
    ans = min(ans, dist[ey1][ex1][3][3]);

    ans = min(ans, dist[ey2][ex2][0][3]);
    ans = min(ans, dist[ey2][ex2][1][3]);
    ans = min(ans, dist[ey2][ex2][2][3]);
    ans = min(ans, dist[ey2][ex2][3][3]);

    cout << (ans == INF ? -1 : ans);

	return 0;
}