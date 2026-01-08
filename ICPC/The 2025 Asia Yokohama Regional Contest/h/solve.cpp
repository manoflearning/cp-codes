#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (x).size()
#define all(x) (x).begin(), (x).end()

int n, m, k;
vector<string> a;
vector<vector<bool>> vis;

pair<bool, bool> line_check(int y1, int y2, int x1, int x2) {
    bool filled = 1, visited = 0;
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            filled &= a[y][x] == '#';
            visited |= vis[y][x];
        }
    }
    return {filled, visited};
}

void coloring(int y1, int y2, int x1, int x2) {
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            vis[y][x] = 1;
        }
    }
}

bool solve() {
    for (int y1 = 0; y1 < n; y1++) {
        for (int x1 = 0; x1 < m; x1++) {
            if (a[y1][x1] != '#') continue;
            if (vis[y1][x1]) continue;
            // cout << y1 << ' ' << x1 << '\n';
            const int y2 = y1 + k - 1;
            const int x2 = x1 + k - 1;

            if (n <= y2 || m <= x2) return 0;

            if (a[y1][x2] != '#' || a[y2][x1] != '#' || a[y2][x2] != '#') return 0;

            auto b1 = line_check(y1, y1, x1, x2);
            if (b1.fr && b1.sc) return 0;
            auto b2 = line_check(y1, y2, x1, x1);
            if (b2.fr && b2.sc) return 0;
            auto b3 = line_check(y2, y2, x1, x2);
            if (b3.fr && b3.sc) return 0;
            auto b4 = line_check(y1, y2, x2, x2);
            if (b4.fr && b4.sc) return 0;

            int cnt = b1.fr + b2.fr + b3.fr + b4.fr;
            if (cnt != 3) return 0;

            if (b1.fr) coloring(y1, y1, x1, x2);
            if (b2.fr) coloring(y1, y2, x1, x1);
            if (b3.fr) coloring(y2, y2, x1, x2);
            if (b4.fr) coloring(y1, y2, x2, x2);
        }
    }
    return 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m >> k;
        
        a.assign(n, string());
        for (auto &i : a) cin >> i;

        vis.assign(n, vector<bool>(m));

        cout << (solve() ? "yes" : "no") << '\n';
    }
}