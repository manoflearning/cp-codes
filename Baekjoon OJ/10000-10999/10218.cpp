#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long dondble
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m, r[15][15], l[15][15], d[15][15], u[15][15], bit;
string a[15], ans, dir;

void init() {
    for (int i = 0; i < 15; i++) {
        a[i].clear();
        for (int j = 0; j < 15; j++) {
            r[i][j] = l[i][j] = u[i][j] = d[i][j] = 0;
        }
    }

    ans = "XHAE";
    bit = 0;
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        a[i].push_back('*');
        for (auto& j : s) a[i].push_back(j);
    }
}

void pre() {
    for (int i = 1; i <= n; i++) {
        int prv = -1;
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != '.' && a[i][j] != 'O') {
                prv = -1;
                continue;
            }

            if (prv == -1) prv = j;
            l[i][j] = prv;
        }

        prv = -1;
        for (int j = m; j >= 1; j--) {
            if (a[i][j] != '.' && a[i][j] != 'O') {
                prv = -1;
                continue;
            }

            if (prv == -1) prv = j;
            r[i][j] = prv;
        }
    }

    for (int j = 1; j <= m; j++) {
        int prv = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i][j] != '.' && a[i][j] != 'O') {
                prv = -1;
                continue;
            }

            if (prv == -1) prv = i;
            u[i][j] = prv;
        }

        prv = -1;
        for (int i = n; i >= 1; i--) {
            if (a[i][j] != '.' && a[i][j] != 'O') {
                prv = -1;
                continue;
            }

            if (prv == -1) prv = i;
            d[i][j] = prv;
        }
    }
}

bool cal2(int y, int x) {
    if (a[y][x] == 'O') return 1;
    
    for (auto& i : dir) {
        if (i == 'R') x = r[y][x];
        if (i == 'L') x = l[y][x];
        if (i == 'U') y = u[y][x];
        if (i == 'D') y = d[y][x];
        
        if (a[y][x] == 'O') return 1;
    }
    return 0;
}

bool cal() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != '.') continue;
            if (!cal2(i, j)) return 0;
        }
    }
    return 1;
}

void bt(int idx) {
    if (bit) return;

    if (cal()) {
        ans = dir;
        bit = 1;
    }
    if (idx == 10 || bit) return;

    if (dir.empty() || dir.back() != 'R') {
        dir.push_back('R');
        bt(idx + 1);
        dir.pop_back();
    }
    if (dir.empty() || dir.back() != 'L') {
        dir.push_back('L');
        bt(idx + 1);
        dir.pop_back();
    }
    if (dir.empty() || dir.back() != 'D') {
        dir.push_back('D');
        bt(idx + 1);
        dir.pop_back();
    }
    if (dir.empty() || dir.back() != 'U') {
        dir.push_back('U');
        bt(idx + 1);
        dir.pop_back();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        pre();

        bt(0);

        cout << ans << '\n';
    }

    return 0;
}