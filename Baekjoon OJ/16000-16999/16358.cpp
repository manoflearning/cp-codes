#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int M = 505;
const int N = 505;
const int INF = 1e9 + 7;

int m, n;
int a[N][M];

int d[M][M], s[M][M];

void input() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (!a[i][j]) a[i][j] = INF;
        }
    }
}

void get_d() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = j + 1; k <= m; k++) {
                d[j][k] += (a[i][j] < a[i][k]);
                d[k][j] += (a[i][j] > a[i][k]);
            }
        }
    }
}

vector<pii> e[N];

void bottomup() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == j) continue;
            if (d[i][j] <= d[j][i]) continue;
            e[d[i][j]].push_back({i, j});
        }
    }
    
    memset(s, -1, sizeof(s));

    for (int i = n - 1; i >= 0; i--) {
        for (auto &[x, y] : e[i]) {
            if (s[x][y] != -1) continue;

            vector<int> lhs, rhs;
            for (int v = 1; v <= m; v++) {
                if (s[v][x] != -1) lhs.push_back(v);
                if (s[y][v] != -1) rhs.push_back(v);
            }

            lhs.push_back(x);
            rhs.push_back(y);

            for (auto &u : lhs) {
                for (auto &v : rhs) {
                    if (s[u][v] == -1) s[u][v] = i;
                }
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    get_d();

    bottomup();

    vector<int> ans;
    for (int i = 1; i <= m; i++) {
        bool is_valid = 1;
        for (int j = 1; j <= m; j++) {
            // cout << s[i][j] << ' ';
            if (s[i][j] < s[j][i]) {
                is_valid = 0;
                break;
            }
        }
        // cout << '\n';
        if (is_valid) ans.push_back(i);
    }

    for (auto &i : ans) cout << i << ' ';
}
