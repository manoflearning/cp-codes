#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int dx[] = {1, -1, 0, 0};
constexpr int dy[] = {0, 0, 1, -1};

vector<vector<int>> f(int n, int m, vector<vector<int>> a) {
    vector<vector<int>> emp;
    vector<vector<int>> ret = a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ret[i][j]) {
                for (int d = 0; d < 4; d++) {
                    int ny = i + dy[d], nx = j + dx[d];
                    if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
                    if (ret[ny][nx] == ret[i][j]) return emp;
                }
            } else {
                vector<int> vis(5);
                for (int d = 0; d < 4; d++) {
                    int ny = i + dy[d], nx = j + dx[d];
                    if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
                    vis[ret[ny][nx]] = 1;
                }

                for (int d = 1; d <= 4; d++) {
                    if (!vis[d]) { ret[i][j] = d; break; };
                    if (d == 4) return emp;
                }
            }
        }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> a(n, vector<int>(m));
        for (auto &i : a) {
            for (auto &j : i) cin >> j;
        }

        vector<vector<int>> ret;
        a[n - 2][m - 2] = 0;
        ret = f(n, m, a);
        if (!ret.empty()) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ret[i][j] << ' ';
                }
                cout << '\n';
            }
            continue;
        }
        a[n - 2][m - 2] = 1;
        ret = f(n, m, a);
        if (!ret.empty()) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ret[i][j] << ' ';
                }
                cout << '\n';
            }
            continue;
        }
        a[n - 2][m - 2] = 2;
        ret = f(n, m, a);
        if (!ret.empty()) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ret[i][j] << ' ';
                }
                cout << '\n';
            }
            continue;
        }
        a[n - 2][m - 2] = 3;
        ret = f(n, m, a);
        if (!ret.empty()) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ret[i][j] << ' ';
                }
                cout << '\n';
            }
            continue;
        }
        a[n - 2][m - 2] = 4;
        ret = f(n, m, a);
        if (!ret.empty()) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ret[i][j] << ' ';
                }
                cout << '\n';
            }
            continue;
        }
        assert(0);
    }
}
