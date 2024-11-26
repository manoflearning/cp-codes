#include <bits/stdc++.h>
using namespace std;

const int dy[] = {1, 0, -1, 0};
const int dx[] = {0, 1, 0, -1};

int n, m;
vector<string> a;

int sty = -1, stx = -1, eny = -1, enx = -1;
vector<vector<int>> dist[4][4];

void bfs() {
    // initialize
    for (int d = 0; d < 4; d++) {
        for (int step = 0; step < 4; step++) {
            dist[d][step].resize(n, vector<int>(m, -1));
        }
    }

    // base case
    struct State {
        int d, step, y, x;
    };
    queue<State> qu;
    for (int d = 0; d < 4; d++) {
        dist[d][0][sty][stx] = 0;
        qu.push({d, 0, sty, stx});
    }

    // inductive step
    while (!qu.empty()) {
        auto [d, step, y, x] = qu.front();
        qu.pop();

        if (y == eny && x == enx) {
            cout << dist[d][step][y][x];
            exit(0);
        }

        for (int nd = 0; nd < 4; nd++) {
            int ny = y + dy[nd], nx = x + dx[nd];
            int nstep = (d == nd ? step + 1 : 1);
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (nstep > 3) continue;
            if (dist[nd][nstep][ny][nx] != -1) continue;
            if (a[ny][nx] == '#') continue;
            dist[nd][nstep][ny][nx] = 1 + dist[d][step][y][x];
            qu.push({nd, nstep, ny, nx});
        }
    }

    cout << -1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (auto &i : a) cin >> i;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') sty = i, stx = j;
            if (a[i][j] == 'T') eny = i, enx = j;
        }

    bfs();
}
