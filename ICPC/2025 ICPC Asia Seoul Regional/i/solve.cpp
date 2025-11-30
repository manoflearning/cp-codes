#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int M = 88;
constexpr int N = 88;

constexpr int dy[] = {1, 0, -1, 0};
constexpr int dx[] = {0, 1, 0, -1};

int m, n;

int a[M][N];
int ans = 0;
bool m3[M][N], is_exist;
set<pii> ab;

void input() {
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    swap(a[r1][c1], a[r2][c2]);
}

void find_match_3() {
    is_exist = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] <= 0) continue;

            if (j + 2 <= n) {
                if (a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2]) {
                    m3[i][j] = m3[i][j + 1] = m3[i][j + 2] = 1;
                    is_exist = 1;
                }
            }
            if (i + 2 <= m) {
                if (a[i][j] == a[i + 1][j] && a[i + 1][j] == a[i + 2][j]) {
                    m3[i][j] = m3[i + 1][j] = m3[i + 2][j] = 1;
                    is_exist = 1;
                }
            }
        }
    }
}

void remove_match_3() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (m3[i][j]) {
                ans++;
                // cout << i << ' ' << j << '\n';
                a[i][j] = -2;
                m3[i][j] = 0;
            }
        }
    }
}

void gravity() {
    for (int j = 1; j <= n; j++) {
        int now{m};
        for (int i = m; i >= 1; i--) {
            if (a[i][j] == -2) continue;

            a[now][j] = a[i][j];
            if (now != i) a[i][j] = -2;
            if (now != i && a[now][j] == 0) ab.insert({now, j});
            now--;
        }
    }
}

void explode() {
    for (const pii v : ab) {
        auto [sty, stx] = v;
        if (a[sty][stx] != 0) continue;

        // cout << "bomb in y = " << sty << ", x = " << stx << '\n';

        queue<pair<pii, int>> qu;

        for (int d = 0; d < 4; d++) {
            qu.push({{sty, stx}, d});
        }
            
        while (!qu.empty()) {
            auto [co, d] = qu.front();
            auto [y, x] = co;
            qu.pop();

            if (a[y][x] != -2) {
                ans++;
                a[y][x] = -2;
            }

            int ny = y + dy[d], nx = x + dx[d];
            if (ny < 1 || m < ny || nx < 1 || n < nx) continue;
            if (a[ny][nx] == -1) continue;
            if (a[ny][nx] == 0 && ab.count({ny, nx})) continue;
            qu.push({{ny, nx}, d});
        }
    }
    ab.clear();
}

void solve() {
    while (1) {
        do {
            // find all match-3 groups
            find_match_3();
            
            // remove all match-3 and adopt gravity
            // and find all activated bombs
            remove_match_3();
            gravity();
        } while (is_exist);

        // explode all activated bombs
        if (ab.empty()) break;
        explode();
        gravity();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);
    
    input();

    solve();

    cout << ans;
}