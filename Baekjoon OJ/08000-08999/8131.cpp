#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXM = 2020, MAXN = 2020;
const int INF = 1e9 + 7;

ll k, t[MAXN][MAXM], pt[MAXN][MAXM];
int m, n;

void input() {
    cin >> k >> m >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> t[i][j];
            pt[i][j] += t[i][j];
            pt[i][j] += pt[i - 1][j];
            pt[i][j] += pt[i][j - 1];
            pt[i][j] -= pt[i - 1][j - 1];
        }
    }
}

inline ll sum(int ys, int xs, int ye, int xe) {
    ll ret = 0;
    ret += pt[ye][xe];
    ret -= pt[ys - 1][xe];
    ret -= pt[ye][xs - 1];
    ret += pt[ys - 1][xs - 1];
    return ret;
}

bool is_valid(int l, int r) {
    int ys = 1, xs = 1, ye = n, xe = m;

    while (1) {
        if (ys == ye && xs == l && xe == r) break;

        if (ys < ye && sum(ys, xs, ys, xe) <= k) ys++;
        else if (ys < ye && sum(ye, xs, ye, xe) <= k) ye--;
        else if (xs < l && sum(ys, xs, ye, xs) <= k) xs++;
        else if (r < xe && sum(ys, xe, ye, xe) <= k) xe--;
        else return 0;
    }

    return sum(ys, xs, ye, xe) <= k;
}

int solve() {
    int ret = INF;
    int xs = 1, xe = 1;
    while (1) {
        bool res = is_valid(xs, xe);

        if (res) ret = min(ret, n + m - (xe - xs + 1));

        if (xs == m && xe == m) break;

        if (xe + 1 <= m && (res || xs == xe)) xe++;
        else xs++;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    int ans = solve();

    swap(n, m);
    for (int i = 1; i <= max(n, m); i++) {
        for (int j = i + 1; j <= max(n, m); j++) {
            swap(t[i][j], t[j][i]);
            swap(pt[i][j], pt[j][i]);
        }
    }
    
    ans = min(ans, solve());

    cout << ans;
}
