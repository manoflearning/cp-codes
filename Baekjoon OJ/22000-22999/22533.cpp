#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

const int dy[] = { 1, 0, -1, 0 };
const int dx[] = { 0, 1, 0, -1 };

// P: 0->1, 3->2, 1->0, 2->3
// Q: 0->3, 1->2, 3->0, 2->1
const int P[4] = { 1, 0, 3, 2 };
const int Q[4] = { 3, 2, 1, 0 };

int n, m, k;
vector<string> a;

struct State {
    int y, x, dir, cntp, cntq;
};

int dist[101][101][4][11][11];
int bfs(int sty, int stx) {
    memset(dist, -1, sizeof(dist));

    deque<State> dq;
    dist[sty][stx][0][0][0] = 0;
    dq.push_back({ sty, stx, 0, 0, 0 });

    while (!dq.empty()) {
        auto [y, x, dir, cntp, cntq] = dq.front();
        dq.pop_front();

        if (a[y][x] == 'G') return dist[y][x][dir][cntp][cntq];
        
        int ny = y + dy[dir], nx = x + dx[dir];
        if (0 <= ny && ny < n && 0 <= nx && nx < m && a[ny][nx] != '#' && a[ny][nx] != 'S') {
            if (dist[ny][nx][dir][cntp][cntq] == -1) {
                dist[ny][nx][dir][cntp][cntq] = dist[y][x][dir][cntp][cntq];
                dq.push_front({ ny, nx, dir, cntp, cntq });
            }
            if (cntp < k && a[ny][nx] == '.') {
                if (dist[ny][nx][P[dir]][1 + cntp][cntq] == -1) {
                    dist[ny][nx][P[dir]][1 + cntp][cntq] = 1 + dist[y][x][dir][cntp][cntq];
                    dq.push_back({ ny, nx, P[dir], 1 + cntp, cntq });
                }
            }
            if (cntq < k && a[ny][nx] == '.') {
                if (dist[ny][nx][Q[dir]][cntp][1 + cntq] == -1) {
                    dist[ny][nx][Q[dir]][cntp][1 + cntq] = 1 + dist[y][x][dir][cntp][cntq];
                    dq.push_back({ ny, nx, Q[dir], cntp, 1 + cntq });
                }
            }
        }
    }

    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if (a[y][x] != 'S') continue;
            cout << bfs(y, x);
            exit(0);
        }
    }
}
