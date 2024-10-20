// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
const int dx[] = { 1, 0, -1, 0, 1, -1, 1, -1 };

int n;
int a[55][55];
int nowy = 1, nowx = 1, d = 0;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int num = 1; num <= n * n - 1; num++) {
        a[nowy][nowx] = num;

        while (1) {
            int ny = nowy + dy[d];
            int nx = nowx + dx[d];
            if (ny < 1 || n < ny || nx < 1 || n < nx || a[ny][nx]) {
                d = (d + 1) % 4;
            }
            else {
                nowy = ny, nowx = nx;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == (n + 1) / 2 && j == (n + 1) / 2) {
                cout << 'T' << ' ';
            }
            else cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}