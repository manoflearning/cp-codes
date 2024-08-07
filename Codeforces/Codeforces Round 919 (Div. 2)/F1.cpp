#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m, q;
vector<string> a;
vector<pii> vol;
vector<vector<int>> dist;
vector<vector<bool>> vis, vis2;
int isly = -1, islx = -1;

void input() {
    cin >> n >> m >> q;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

void volBfs() {
    dist.resize(n, vector<int>(m, -1));

    queue<pii> q;
    for (auto& i : vol) {
        q.push({ i.fr, i.sc });
        dist[i.fr][i.sc] = 0;
    }

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (dist[ny][nx] != -1) continue;
            q.push({ ny, nx });
            dist[ny][nx] = dist[y][x] + 1;
        }
    }
}

void dfs(int y, int x, int lb) {
    vis[y][x] = 1;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        if (vis[ny][nx]) continue;
        if (dist[ny][nx] < lb) continue;
        if (a[ny][nx] == '#') continue;
        dfs(ny, nx, lb);
    }
}

bool dfs2(int y, int x) {
    bool ret = (y == 0 || y == n - 1 || x == 0 || x == m - 1);

    vis2[y][x] = 1;
    for (int i = 0; i < 8; i++) {
        if (ret) break;
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        if (vis2[ny][nx]) continue;
        if (vis[ny][nx]) continue;
        ret |= dfs2(ny, nx);
    }
    return ret;
}

bool isValid(int sty, int stx, int lb) {
    if (dist[sty][stx] < lb) return false;

    vis.clear();
    vis.resize(n, vector<bool>(m));

    dfs(sty, stx, lb);

    vis2.clear();
    vis2.resize(n, vector<bool>(m));

    return !dfs2(isly, islx);
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
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'v') 
                vol.push_back({ i, j });
            if (a[i][j] == '#' && isly == -1)
                isly = i, islx = j;
        }
    }

    volBfs();

    for (int i = 0; i < q; i++) {
        int y, x;
        cin >> y >> x;
        y--, x--;

        int l = 0, r = n + m;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (isValid(y, x, mid)) l = mid;
            else r = mid - 1;
        }

        cout << l << '\n';
    }
}