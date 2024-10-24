#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int MAXN = 1010;
const int INF = 1e9 + 7;

int n, k;
vector<pii> adj[MAXN];

vector<int> dp[MAXN][2];
int siz[MAXN];
vector<vector<tuple<int, int, int>>> optv[MAXN][2];

void input() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs(int v, int prv) {
    siz[v] = 1;
    dp[v][0].resize(siz[v] + 1, INF);
    dp[v][1].resize(siz[v] + 1, INF);
    optv[v][0].resize(siz[v] + 1);
    optv[v][1].resize(siz[v] + 1);
    
    dp[v][0][0] = dp[v][1][1] = 0;
    
    for (auto &[w, u] : adj[v]) {
        if (u == prv) continue;
        dfs(u, v);

        vector<vector<int>> tmp(2, vector<int>(siz[v] + siz[u] + 1, INF));
        vector<vector<vector<tuple<int, int, int>>>> tmpv(2, vector<vector<tuple<int, int, int>>>(siz[u] + siz[v] + 1));

        for (int x = 0; x <= siz[v]; x++) {
            for (int y = 0; y <= siz[u]; y++) {
                if (tmp[0][x + y] > dp[v][0][x] + dp[u][1][y]) {
                    tmp[0][x + y] = dp[v][0][x] + dp[u][1][y];
                    tmpv[0][x + y] = optv[v][0][x];
                    tmpv[0][x + y].push_back({u, 1, y});
                }
                if (tmp[0][x + y] > w + dp[v][0][x] + dp[u][0][y]) {
                    tmp[0][x + y] = w + dp[v][0][x] + dp[u][0][y];
                    tmpv[0][x + y] = optv[v][0][x];
                    tmpv[0][x + y].push_back({u, 0, y});
                }
                if (tmp[1][x + y] > dp[v][1][x] + dp[u][0][y]) {
                    tmp[1][x + y] = dp[v][1][x] + dp[u][0][y];
                    tmpv[1][x + y] = optv[v][1][x];
                    tmpv[1][x + y].push_back({u, 0, y});
                }
                if (tmp[1][x + y] > w + dp[v][1][x] + dp[u][1][y]) {
                    tmp[1][x + y] = w + dp[v][1][x] + dp[u][1][y];
                    tmpv[1][x + y] = optv[v][1][x];
                    tmpv[1][x + y].push_back({u, 1, y});
                }
            }
        }

        dp[v][0] = tmp[0];
        dp[v][1] = tmp[1];
        optv[v][0] = tmpv[0];
        optv[v][1] = tmpv[1];

        siz[v] += siz[u];
    }
}

vector<int> ans2;
void backtrace(int v, int bit, int rem) {
    if (bit) ans2.push_back(v);

    for (auto &i : optv[v][bit][rem]) {
        backtrace(get<0>(i), get<1>(i), get<2>(i));
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
    
    dfs(1, 0);

    cout << min(dp[1][0][k], dp[1][1][k]) << '\n';
    if (dp[1][0][k] <= dp[1][1][k]) backtrace(1, 0, k);
    else backtrace(1, 1, k);
    sort(all(ans2));
    for (auto& i : ans2) cout << i << ' ';
}
