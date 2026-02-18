#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int h, w;
    cin >> h >> w;

    vector<string> a(h);
    for (auto &i : a) cin >> i;

    ll area = 0;
    for (auto &i : a) for (auto &j : i) area += (j == '#');

    ll ans = -1;
    for (ll p = 1; p * p <= area; p++) {
        if (area % (p * p)) continue;

        bool yes = 1;

        vector<vector<int>> vis(h + 1, vector<int>(w + 1));
        for (int x = 0; x < h; x++) {
            for (int y = 0; y < w; y++) {
                if (x > 0) vis[x][y] += vis[x - 1][y];
                if (y > 0) vis[x][y] += vis[x][y - 1];
                if (x > 0 && y > 0) vis[x][y] -= vis[x - 1][y - 1];

                if (vis[x][y] > 1) yes = 0;

                if (vis[x][y]) {
                    if (a[x][y] == '.') yes = 0;
                } else {
                    if (a[x][y] == '#') {
                        if (x + p <= h && y + p <= w) {
                            vis[x][y]++;
                            vis[x + p][y]--;
                            vis[x][y + p]--;
                            vis[x + p][y + p]++;
                        } else {
                            yes = 0;
                        }
                    }
                }
            }
        }

        if (yes) {
            ans = p;

            // DEBUG
            // for (int x = 0; x < h; x++) {
            //     for (int y = 0; y < w; y++) {
            //         cout << vis[x][y] << ' ';
            //     }
            //     cout << '\n';
            // }
            // cout << '\n';
        }
    }
    assert(ans != -1);
    cout << ans << '\n';
}
