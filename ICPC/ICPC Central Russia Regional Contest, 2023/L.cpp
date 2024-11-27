#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int dy[2][6] = {
    {0, 0, 1, 1, -1, -1},
    {0, 0, 1, 1, -1, -1},
};
const int dx[2][6] = {
    {1, -1, -1, 0, -1, 0},
    {1, -1, 0, 1, 0, 1},
};

int n, m;
vector<string> a;
int dist[1010][1010];

void bfs() {
    memset(dist, -1, sizeof(dist));

    deque<pii> dq;
    for (int x = 0; x < m; x++) {
        if (a[0][x] == '.') {
            dist[0][x] = 1;
            dq.push_back({0, x});
        }
        else {
            dist[0][x] = 0;
            dq.push_front({0, x});
        }
    }

    while (!dq.empty()) {
        auto [y, x] = dq.front();
        dq.pop_front();

        if (y == n - 1) {
            cout << dist[y][x];
            exit(0);
        }

        for (int d = 0; d < 6; d++) {
            int ny = y + dy[y & 1][d], nx = x + dx[y & 1][d];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (dist[ny][nx] != -1) continue;

            if (a[ny][nx] == '.') {
                dist[ny][nx] = 1 + dist[y][x];
                dq.push_back({ny, nx});
            } else {
                dist[ny][nx] = dist[y][x];
                dq.push_front({ny, nx});
            }
        }
    }

    assert(0);
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

    bfs();
}
