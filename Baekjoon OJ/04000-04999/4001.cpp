#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int INF = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, 1, -1, -1 };

int w, h;
vector<string> a;

void input() {
    cin >> w >> h;
    a.resize(h + 2);
    a[0] = string(w + 2, '*');
    for (int i = 1; i <= h; i++) {
        cin >> a[i];
        a[i] = '*' + a[i] + '*';
    }
    a[h + 1] = string(w + 2, '*');
}

void dfs(int y, int x, vector<vector<bool>>& vis) {
    vis[y][x] = 1;
    for (int d = 0; d < 8; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 1 || h < ny || nx < 1 || w < nx) continue;
        if (a[ny][nx] != '#') continue;
        if (vis[ny][nx]) continue;
        dfs(ny, nx, vis);
    }
}

vector<vector<bool>> vis1, vis2;
void labeling() {
    vis1.resize(h + 2, vector<bool>(w + 2));
    vis2.resize(h + 2, vector<bool>(w + 2));
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (a[i][j] == '.') continue;
            if ((i == h || j == 1) && !vis1[i][j]) dfs(i, j, vis1);
            if ((i == 1 || j == w) && !vis2[i][j]) dfs(i, j, vis2);
        }
    }
}

vector<vector<int>> psum_all, psum_1, psum_2;
void build_psum() {
    psum_all.resize(h + 2, vector<int>(w + 2));
    psum_1.resize(h + 2, vector<int>(w + 2));
    psum_2.resize(h + 2, vector<int>(w + 2));

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (i == 1 && j == 1) continue;
            if (i == h && j == w) continue;

            if (a[i][j] == '#') psum_all[i][j] = 1;
            
            if (a[i][j] == '#' && vis1[i][j]) psum_1[i][j] = 1;
            if (i == h) psum_1[i + 1][j] = 1;
            if (j == 1) psum_1[i][j - 1] = 1;

            if (a[i][j] == '#' && vis2[i][j]) psum_2[i][j] = 1;
            if (i == 1) psum_2[i - 1][j] = 1;
            if (j == w) psum_2[i][j + 1] = 1;
        }
    }

    for (int i = 0; i <= h + 1; i++) {
        for (int j = 0; j <= w + 1; j++) {
            if (j > 0) psum_all[i][j] += psum_all[i][j - 1];
            if (i > 0) psum_all[i][j] += psum_all[i - 1][j];
            if (j > 0 && i > 0) psum_all[i][j] -= psum_all[i - 1][j - 1];

            if (j > 0) psum_1[i][j] += psum_1[i][j - 1];
            if (i > 0) psum_1[i][j] += psum_1[i - 1][j];
            if (j > 0 && i > 0) psum_1[i][j] -= psum_1[i - 1][j - 1];

            if (j > 0) psum_2[i][j] += psum_2[i][j - 1];
            if (i > 0) psum_2[i][j] += psum_2[i - 1][j];
            if (j > 0 && i > 0) psum_2[i][j] -= psum_2[i - 1][j - 1];
        }
    }
}

inline int sum_all(int sy, int sx, int ey, int ex) {
    int ret = 0;
    ret += psum_all[ey][ex];
    if (sy > 0) ret -= psum_all[sy - 1][ex];
    if (sx > 0) ret -= psum_all[ey][sx - 1];
    if (sy > 0 && sx > 0) ret += psum_all[sy - 1][sx - 1];
    return ret;
}
inline int sum_1(int sy, int sx, int ey, int ex) {
    int ret = 0;
    ret += psum_1[ey][ex];
    if (sy > 0) ret -= psum_1[sy - 1][ex];
    if (sx > 0) ret -= psum_1[ey][sx - 1];
    if (sy > 0 && sx > 0) ret += psum_1[sy - 1][sx - 1];
    return ret;
}
inline int sum_2(int sy, int sx, int ey, int ex) {
    int ret = 0;
    ret += psum_2[ey][ex];
    if (sy > 0) ret -= psum_2[sy - 1][ex];
    if (sx > 0) ret -= psum_2[ey][sx - 1];
    if (sy > 0 && sx > 0) ret += psum_2[sy - 1][sx - 1];
    return ret;
}

int opt_len = INF, opt_y = -1, opt_x = -1;
void solve() {
    for (int y = 1; y <= h; y++) {
        for (int x = 1; x <= w; x++) {
            if (a[y][x] == '#') continue;
            if (y == 1 && x == 1) continue;
            if (y == h && x == w) continue;

            int l = 1, r = min(h - y + 1, w - x + 1);
            if (y + r - 1 == h && x + r - 1 == w) r--;
            
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (sum_all(y, x, y + mid - 1, x + mid - 1)) r = mid - 1;
                else l = mid;
            }

            l = 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                bool res = 1;
                res &= (sum_1(y - 1, x - 1, y + mid, x + mid) > 0);
                res &= (sum_2(y - 1, x - 1, y + mid, x + mid) > 0);
                if (res) r = mid;
                else l = mid + 1;
            }

            bool res = 1;
            res &= (sum_1(y - 1, x - 1, y + l, x + l) > 0);
            res &= (sum_2(y - 1, x - 1, y + l, x + l) > 0);

            if (res && opt_len > l) {
                opt_len = l;
                opt_y = y, opt_x = x;
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

    input();

    labeling();

    build_psum();

    solve();

    if (opt_len == INF) cout << "Impossible";
    else cout << opt_len << ' ' << opt_x << ' ' << opt_y;
}
