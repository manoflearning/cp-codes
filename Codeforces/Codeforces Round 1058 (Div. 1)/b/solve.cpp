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
constexpr int M = 505;

int n, m;
vector<string> arr;
vector<bitset<M>> a;
vector<vector<int>> ans;

void init() {
    arr.clear();
    a.clear();
    ans.clear();
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        arr.push_back(s);
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
            vector<bitset<M>> tmp(m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    tmp[j][i] = (arr[i][j] == '1');
                }
            }
            swap(n, m);
            a = tmp;
        } else {
            a.resize(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    a[i][j] = (arr[i][j] == '1');
                }
            }
        }

        ans.resize(n, vector<int>(m, INF));

        for (int len = 2; len <= m; len++) {
            vector<int> mp(m, -1);
            for (int eny = 0; eny < n; eny++) {
                bitset<M> mask{};
                for (int i = 1; i < len - 1; i++) mask[i] = 1;

                for (int stx = 0; stx + len - 1 < m; stx++) {
                    int enx = stx + len - 1;

                    bool is_valid = 1;
                    is_valid &= a[eny][stx];
                    is_valid &= a[eny][enx];

                    int sty = mp[stx];
                    is_valid &= (sty != -1 && !(a[sty] & a[eny] & mask).any());

                    if (is_valid) {
                        coloring(sty, stx, eny, enx);
                    }

                    if (a[eny][stx] && a[eny][enx]) mp[stx] = eny;

                    mask <<= 1;
                }
            }
        }
        
        if (is_swaped) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << (ans[j][i] == INF ? 0 : ans[j][i]) << ' ';
                }
                cout << '\n';
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << (ans[i][j] == INF ? 0 : ans[i][j]) << ' ';
                }
                cout << '\n';
            }
        }
    }
}
