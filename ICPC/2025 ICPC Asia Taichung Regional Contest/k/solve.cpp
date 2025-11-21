#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define aint(x) (x).begin(), (x).end()

constexpr int dy[] = {1, 0, -1, 0, 1, 1, -1, -1};
constexpr int dx[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, m, q;
vector<string> a;
int ans[1010101];

struct node { int now{}, mul{}, sum{}; };
vector<vector<node>> dp(1010, vector<node>(1010));

void bfs(int sty, int stx) {
    ans[a[sty][stx] - '0']++;

    queue<pair<pii, int>> qu;
    dp[sty][stx] = {a[sty][stx] - '0', 1, a[sty][stx] - '0'};
    for (int d = 0; d < 8; d++)
        qu.push({{sty, stx}, d});
    
    while (!qu.empty()) {
        auto [co, d] = qu.front();
        auto [y, x] = co;
        qu.pop();

        if (1010101 <= dp[y][x].sum) continue;
        if ((y != sty || x != stx) && '1' <= a[y][x] && a[y][x] <= '9') {
            // if (dp[y][x].sum == 727) {
            //     cout << sty << ' ' << stx << ' ';
            //     cout << y << ' ' << x << ' ' << dp[y][x].now << ' ' << dp[y][x].sum << '\n';
            // }

            ans[dp[y][x].sum]++;
        }
        // if (sty == 0 && stx == 3 && y == 0 && x == 4) {
        //     cout << sty << ' ' << stx << ' ';
        //     cout << y << ' ' << x << ' ' << dp[y][x].now << ' ' << dp[y][x].mul << ' ' << dp[y][x].sum << '\n';
        // }

        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;

        if ('1' <= a[ny][nx] && a[ny][nx] <= '9') {
            if (a[y][x] == '*') {
                int diff = dp[y][x].now * (a[ny][nx] - '0') - dp[y][x].now;
                dp[ny][nx].mul = dp[y][x].now;
                dp[ny][nx].now = dp[y][x].now + diff;
                dp[ny][nx].sum = dp[y][x].sum + diff;
                qu.push({{ny, nx}, d});
            } else if (a[y][x] == '+') {
                int diff = (a[ny][nx] - '0');
                dp[ny][nx].mul = 1;
                dp[ny][nx].now = diff;
                dp[ny][nx].sum = dp[y][x].sum + diff;
                qu.push({{ny, nx}, d});
            } else {
                int diff = dp[y][x].now * 10 + dp[y][x].mul * (a[ny][nx] - '0') - dp[y][x].now;
                dp[ny][nx].mul = dp[y][x].mul;
                dp[ny][nx].now = dp[y][x].now + diff;
                dp[ny][nx].sum = dp[y][x].sum + diff;
                qu.push({{ny, nx}, d});
            }
        } else {
            if (a[y][x] == '+' || a[y][x] == '*') continue;

            dp[ny][nx] = dp[y][x];
            qu.push({{ny, nx}, d});
        }
    }
}    

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> q;
    a.resize(n);
    for (auto &i : a) cin >> i;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if ('1' <= a[y][x] && a[y][x] <= '9')
                bfs(y, x);
        }
    }

    while (q--) {
        int x; cin >> x;
        cout << ans[x] << '\n';
    }
}