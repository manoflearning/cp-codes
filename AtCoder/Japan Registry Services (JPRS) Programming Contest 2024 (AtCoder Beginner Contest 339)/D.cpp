// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int n;
vector<string> a;
int sx1 = -1, sy1 = -1, sx2 = -1, sy2 = -1;
int dist[66][66][66][66];

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 'P') {
                if (sx1 == -1) sx1 = i, sy1 = j;
                else sx2 = i, sy2 = j;
            }
        }
    }

    memset(dist, -1, sizeof(dist));

    queue<pair<pii, pii>> q;
    q.push({ { sx1, sy1 }, { sx2, sy2 }});
    dist[sx1][sy1][sx2][sy2] = 0;
    while (!q.empty()) {
        auto [x1, y1] = q.front().fr;
        auto [x2, y2] = q.front().sc;
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx1 = x1 + dx[d], ny1 = y1 + dy[d];
            int nx2 = x2 + dx[d], ny2 = y2 + dy[d];
            if (nx1 < 0 || n <= nx1 || ny1 < 0 || n <= ny1) {
                nx1 = x1, ny1 = y1;
            }
            else if (a[nx1][ny1] == '#') nx1 = x1, ny1 = y1;
            if (nx2 < 0 || n <= nx2 || ny2 < 0 || n <= ny2) {
                nx2 = x2, ny2 = y2;
            }
            else if (a[nx2][ny2] == '#') nx2 = x2, ny2 = y2;

            if (dist[nx1][ny1][nx2][ny2] != -1) continue;

            dist[nx1][ny1][nx2][ny2] = dist[x1][y1][x2][y2] + 1;
            q.push({ { nx1, ny1 }, { nx2, ny2 }});
        }
    }

    int ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j][i][j] == -1) continue;
            ans = min(ans, dist[i][j][i][j]);
        }
    }

    cout << (ans == INF ? -1 : ans);
}