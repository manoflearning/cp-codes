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
const int dy[] = { 1, -1, 2, 2, -2, -2, -1, 1 };
const int dx[] = { 2, 2, 1, -1, 1, -1, -2, -2 };

int a[10][10], b[10][10];
int done[10][10], ans = INF;
int dist[10][10][10][10];

int bfs(int sy, int sx) {
    queue<pii> q;
    dist[sy][sx][sy][sx] = 0;
    q.push({ sy, sx });

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 1 || 4 < ny || nx < 1 || 4 < nx) continue;
            if (dist[sy][sx][ny][nx] != -1) continue;
            dist[sy][sx][ny][nx] = dist[sy][sx][y][x] + 1;
            q.push({ ny, nx });
        }
    }

    return 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 1; i <= 4; i++) {
        string s; cin >> s;
        for (int j = 1; j <= 4; j++) {
            a[i][j] = (s[j - 1] == '1');
        }
    }

    for (int i = 1; i <= 4; i++) {
        string s; cin >> s;
        for (int j = 1; j <= 4; j++) {
            b[i][j] = (s[j - 1] == '1');
        }
    }

    memset(dist, -1, sizeof(dist));

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            bfs(i, j);
        }
    }

    vector<pii> pa, pb;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (a[i][j] == 1 && b[i][j] == 1) continue;

            if (a[i][j] == 1) pa.push_back({ i, j });
            if (b[i][j] == 1) pb.push_back({ i, j });
        }
    }

    vector<int> ord(sz(pa));
    for (int i = 0; i < sz(pa); i++) ord[i] = i;

    do {
        int res = 0;
        for (int i = 0; i < sz(pa); i++) {
            auto [sy, sx] = pa[ord[i]];
            auto [ey, ex] = pb[i];

            if (dist[sy][sx][ey][ex] == -1) res = INF;
            else res += dist[sy][sx][ey][ex];
        }
        ans = min(ans, res);
    } while (next_permutation(all(ord)));
    
    cout << ans;
}