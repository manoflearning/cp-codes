#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 2020;
const int MAXK = 1010;

void add(array<short, 4> &x, int val) {
    for (int i = 0; i < 4; i++) {
        if (x[i] == val) break;
        if (!x[i]) { x[i] = val; break; }
    }
}
void merge(const array<short, 4> &a, const array<short, 4> &b, array<short, 4> &c) {
    for (auto &i : a) {
        for (int j = 0; j < 4; j++) {
            if (c[j] == i) break;
            if (!c[j]) { c[j] = i; break; }
        }
    }
    for (auto &i : b) {
        for (int j = 0; j < 4; j++) {
            if (c[j] == i) break;
            if (!c[j]) { c[j] = i; break; }
        }
    }
}

int n, k;
short a[MAXN][MAXN];
array<short, 4> ul[MAXN][MAXN], ur[MAXN][MAXN], dl[MAXN][MAXN], dr[MAXN][MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            merge(ul[i][j - 1], ul[i - 1][j], ul[i][j]);
            if (a[i][j]) add(ul[i][j], a[i][j]);
        }
        for (int j = n; j >= 1; j--) {
            merge(ur[i][j + 1], ur[i - 1][j], ur[i][j]);
            if (a[i][j]) add(ur[i][j], a[i][j]);
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            merge(dl[i][j - 1], dl[i + 1][j], dl[i][j]);
            if (a[i][j]) add(dl[i][j], a[i][j]);
        }
        for (int j = n; j >= 1; j--) {
            merge(dr[i][j + 1], dr[i + 1][j], dr[i][j]);
            if (a[i][j]) add(dr[i][j], a[i][j]);
        }
    }

    int ans = 0;
    bitset<MAXK> vis;
    for (int i = 2; i <= n - 1; i++) {
        for (int j = 2; j <= n - 1; j++) {
            if (a[i][j]) continue;

            bool res = 0;
            for (auto p1 : ul[i - 1][j - 1]) if (p1) {
                vis[p1] = 1;
                for (auto p2 : ur[i - 1][j + 1]) if (p2 && !vis[p2]) {
                    vis[p2] = 1;
                    for (auto p3 : dl[i + 1][j - 1]) if (p3 && !vis[p3]) {
                        vis[p3] = 1;
                        for (auto p4 : dr[i + 1][j + 1]) if (p4 && !vis[p4]) {
                            res = 1; break;
                        }
                        vis[p3] = 0;
                        if (res) break;
                    }
                    vis[p2] = 0;
                    if (res) break;
                }
                vis[p1] = 0;
                if (res) break;
            }

            ans += res;
        }
    }

    cout << ans;
}
