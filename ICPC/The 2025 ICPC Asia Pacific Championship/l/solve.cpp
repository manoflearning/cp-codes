#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int dy[] = {1, 0, -1, 0};
constexpr int dx[] = {0, 1, 0, -1};

int r, c, n, p;
vector<vi> g;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> r >> c >> n >> p;
    g.assign(r, vi(c));

    map<int, pii> rg;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            cin >> g[i][j];
            if (g[i][j]) rg[g[i][j]] = {i, j};
        }

    set<int> vis;
    for (int i = 1; i <= p; i++) {
        const auto [y, x] = rg[i];
        const int t = (p - i);
        for (int d = 0; d < 4; d++) {
            const int ny = y + dy[d], nx = x + dx[d];
            if (ny < 0 || r <= ny || nx < 0 || c <= nx) continue;
            if (g[ny][nx] > 0 && g[ny][nx] + t <= n) vis.insert(g[ny][nx] + t);
        }
    }

    // DEBUG
    // for (auto &i : vis) cout << i << ' ';
    // cout << '\n';

    cout << sz(vis) << "/" << n - 1;
}
