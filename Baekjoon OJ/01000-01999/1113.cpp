//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size() 

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m, a[55][55];
int vi[55][55];

int isDone() {
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (!vi[r][c]) return 0;
        }
    }
    return 1;
}

int modify() {
    int ret = 0;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (vi[r][c]) continue;
            for (int d = 0; d < 4; d++) {
                int nr = r + dy[d], nc = c + dx[d];
                if (nr < 1 || n < nr || nc < 1 || m < nc) continue;
                if (vi[nr][nc] && a[nr][nc] <= a[r][c]) {
                    vi[r][c] = 1;
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

int ans = 0;

void add() {
    int mn = INF;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (vi[r][c]) continue;
            mn = min(mn, a[r][c]);
        }
    }
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (vi[r][c] || mn < a[r][c]) continue;
            ans++, a[r][c]++;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int r = 1; r <= n; r++) {
        string s; cin >> s;
        for (int c = 1; c <= m; c++) {
            a[r][c] = s[c - 1] - '0';
        }
    }

    for (int r = 1; r <= n; r++)
        vi[r][1] = vi[r][m] = 1;
    for (int c = 1; c <= m; c++)
        vi[1][c] = vi[n][c] = 1;

    while (!isDone()) {
        while (modify());
        add();
    }

    cout << ans;
}