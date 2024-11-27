#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 1010, MAXM = 1010;

int n, m;
vector<string> a;
string s;
int pd[MAXN][MAXM], pu[MAXN][MAXM], pl[MAXN][MAXM], pr[MAXN][MAXM];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (auto &i : a) cin >> i;
    cin >> s;

    for (int i = 0; i < n / 2; i++)
        swap(a[i], a[n - i - 1]);

    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            if (a[x][y] == '#') continue;
            if (x == 0 || (x > 0 && a[x - 1][y] == '#')) pd[x][y] = x;
            else pd[x][y] = pd[x - 1][y];
        }
        for (int x = n - 1; x >= 0; x--) {
            if (a[x][y] == '#') continue;
            if (x == n - 1 || (x < n - 1 && a[x + 1][y] == '#')) pu[x][y] = x;
            else pu[x][y] = pu[x + 1][y];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '#') continue;
            if (j == 0 || (j > 0 && a[i][j - 1] == '#')) pl[i][j] = j;
            else pl[i][j] = pl[i][j - 1];
        }
        for (int j = m - 1; j >= 0; j--) {
            if (a[i][j] == '#') continue;
            if (j == m - 1 || (j < m - 1 && a[i][j + 1] == '#')) pr[i][j] = j;
            else pr[i][j] = pr[i][j + 1];
        }
    }

    int y = 0, x = 0;
    for (auto c : s) {
        int ny = y, nx = x;
        if (c == 'D') ny = pd[y][x];
        else if (c == 'U') ny = pu[y][x];
        else if (c == 'L') nx = pl[y][x];
        else if (c == 'R') nx = pr[y][x];
        y = ny, x = nx;
    }

    cout << x + 1 << ' ' << y + 1;
}
