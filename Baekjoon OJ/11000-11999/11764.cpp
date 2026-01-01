#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;
// constexpr int NR = 10101;
// constexpr int NC = 10101;

vector<vector<int>> ps_n, ps_m;
// int8_t ps_n[NR][NC], ps_m[NR][NC];

int get_n(int sx, int ex, int sy, int ey) {
    int ret = 0;
    ret += ps_n[ex][ey];
    ret -= ps_n[sx - 1][ey];
    ret -= ps_n[ex][sy - 1];
    ret += ps_n[sx - 1][sy - 1];
    return ret;
}
int get_m(int sx, int ex, int sy, int ey) {
    int ret = 0;
    ret += ps_m[ex][ey];
    ret -= ps_m[sx - 1][ey];
    ret -= ps_m[ex][sy - 1];
    ret += ps_m[sx - 1][sy - 1];
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int nr, nc, n, m;
    cin >> nr >> nc >> n >> m;

    if (n == 0) {
        cout << 0 << '\n';
        exit(0);
    }

    vector<pii> a(n + m);
    for (auto &i : a) {
        cin >> i.fr >> i.sc;
        i.fr += 7, i.sc += 4;
    }

    vector<int> cc_x(1, -INF), cc_y(1, -INF);
    cc_x.push_back(0);
    cc_y.push_back(0);
    for (auto &i : a) {
        cc_x.push_back(i.fr);
        cc_y.push_back(i.sc);
    }
    cc_x.push_back(nr - 1);
    cc_y.push_back(nc - 1);

    sort(all(cc_x));
    sort(all(cc_y));
    cc_x.erase(unique(all(cc_x)), cc_x.end());
    cc_y.erase(unique(all(cc_y)), cc_y.end());

    ps_n.resize(sz(cc_x), vector<int>(sz(cc_y)));
    ps_m.resize(sz(cc_x), vector<int>(sz(cc_y)));

    for (int i = 0; i < n + m; i++) {
        a[i].fr = lower_bound(all(cc_x), a[i].fr) - cc_x.begin();
        a[i].sc = lower_bound(all(cc_y), a[i].sc) - cc_y.begin();

        if (i < n) {
            ps_n[a[i].fr][a[i].sc]++;
        } else {
            ps_m[a[i].fr][a[i].sc]++;
        }
    }

    for (int i = 1; i < sz(cc_x); i++) {
        for (int j = 1; j < sz(cc_y); j++) {
            ps_n[i][j] += ps_n[i - 1][j];
            ps_n[i][j] += ps_n[i][j - 1];
            ps_n[i][j] -= ps_n[i - 1][j - 1];

            ps_m[i][j] += ps_m[i - 1][j];
            ps_m[i][j] += ps_m[i][j - 1];
            ps_m[i][j] -= ps_m[i - 1][j - 1];
        }
    }

    int ans = INF;
    for (int i = 1; i < sz(cc_x); i++) {
        for (int j = i; j < sz(cc_x); j++) {
            for (int p = 1; p < sz(cc_y); p++) {
                for (int q = p; q < sz(cc_y); q++) {
                    if (nr - 1 < cc_x[j]) continue;
                    if (nc - 1 < cc_y[q]) continue;

                    int res = 0;

                    res += n - get_n(i, j, p, q);
                    res += get_m(i, j, p, q);

                    ans = min(ans, res);
                }
            }
        }
    }

    cout << ans << '\n';
}