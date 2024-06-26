#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int dy[] = { 1, -1, 0, 0 };
const int dx[] = { 0, 0, 1, -1 };

int n, m, a[111][111];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
}

int dist[111][111];

int mx = 0;

void bfs01() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dist[i][j] = -1;
        }
    }

    deque<pii> q;
    dist[1][1] = 0;
    q.push_back({ 1, 1 });

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop_front();

        mx = max(mx, dist[y][x]);

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
            if (dist[ny][nx] != -1) continue;

            if (a[ny][nx]) {
                dist[ny][nx] = dist[y][x] + 1;
                q.push_back({ ny, nx });
            }
            else {
                dist[ny][nx] = dist[y][x];
                q.push_front({ ny, nx });
            }
        }
    }
}

void print() {
    cout << mx << '\n';
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (dist[i][j] == mx && a[i][j]) cnt++;
        }
    }
    cout << cnt;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    bfs01();

    print();
}