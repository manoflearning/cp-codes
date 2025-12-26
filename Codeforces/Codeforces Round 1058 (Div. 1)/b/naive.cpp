#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

int n, m;
vector<vector<bool>> a;
vector<vector<int>> ans;

void init() {
    a.clear();
    ans.clear();
}

void input() {
    cin >> n >> m;
    a.resize(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = (s[j] == '1');
        }
    }
}

void coloring(int sty, int stx, int eny, int enx) {
    int co = (eny - sty + 1) * (enx - stx + 1);
    for (int y = sty; y <= eny; y++) {
        for (int x = stx; x <= enx; x++) {
            ans[y][x] = min(ans[y][x], co);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();
        
        input();

        bool is_swaped = 0;
        if (n < m) {
            is_swaped = 1;
            vector<vector<bool>> tmp(m, vector<bool>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    tmp[j][i] = a[i][j];
                }
            }
            swap(n, m);
            a = tmp;
        }
        ans.resize(n, vector<int>(m, INF));

        for (int len = 2; len <= m; len++) {
            vector<int> mp(m, -1);
            for (int eny = 0; eny < n; eny++) {
                for (int stx = 0; stx + len - 1 < m; stx++) {
                    int enx = stx + len - 1;
                    if (a[eny][stx] && a[eny][enx]) {
                        if (mp[stx] != -1) {
                            int sty = mp[stx];
                            coloring(sty, stx, eny, enx);
                        }
                        mp[stx] = eny;
                    }
                }
            }
        }
        
        if (is_swaped) {
            vector<vector<int>> tmp(m, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    tmp[j][i] = ans[i][j];
                }
            }
            swap(n, m);
            ans = tmp;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << (ans[i][j] == INF ? 0 : ans[i][j]) << ' ';
            }
            cout << '\n';
        }
    }
}
