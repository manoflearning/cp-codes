#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
constexpr int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};

constexpr ld INF = 4e18;
constexpr ld EPS = 1e-8;
constexpr ld PI = 3.14159265358979323846264338327950288l;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    int h, w;
    cin >> h >> w;

    vector<string> a(h);
    for (auto &i : a) cin >> i;

    vector<vector<ld>> dist(2 * h + 1, vector<ld>(2 * w + 1, INF));
    priority_queue<tuple<ld, int, int>, vector<tuple<ld, int, int>>, greater<>> pq;
    
    dist[0][0] = .0l;
    pq.push({dist[0][0], 0, 0});

    while (!pq.empty()) {
        const auto [cost, x, y] = pq.top();
        pq.pop();

        if (dist[x][y] < cost) continue;

        for (int d = 0; d < 4; d++) {
            const int nx = x + dx[d], ny = y + dy[d];
            const ld ncost = cost + 5;
            if (nx < 0 || 2 * h + 1 <= nx || ny < 0 || 2 * w + 1 <= ny) continue;
            if (((x & 1) && y != ny) || ((y & 1) && x != nx)) continue;
            if (dist[nx][ny] <= ncost) continue;

            dist[nx][ny] = ncost;
            pq.push({dist[nx][ny], nx, ny});
        }

        if ((x + y) & 1) {
            for (int d = 4; d < 8; d++) {
                const int nx = x + dx[d], ny = y + dy[d];
                const ld ncost = cost + PI * 2.5l;
                if (nx < 0 || 2 * h + 1 <= nx || ny < 0 || 2 * w + 1 <= ny) continue;
                if (a[min(x, nx) / 2][min(y, ny) / 2] != 'O') continue;
                if (dist[nx][ny] <= ncost) continue;

                dist[nx][ny] = ncost;
                pq.push({dist[nx][ny], nx, ny});
            }
        }
    }

    // DEBUG
    // for (int x = 0; x <= 2 * h; x++) {
    //     for (int y = 0; y <= 2 * w; y++) {
    //         cout << (INF == dist[x][y] ? -1 : dist[x][y]) << ' ';
    //     }
    //     cout << '\n';
    // }

    cout << fixed;
    cout.precision(10);

    cout << dist[2 * h][2 * w] << '\n';
}
