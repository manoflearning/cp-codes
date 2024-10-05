#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;
const int MAXN = 101010;
const int MAXB = 505;

int n, a, b;
vector<int> adj[MAXN];

void input() {
    cin >> n >> a >> b;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

ll dp[MAXN][MAXB];
int tmp[MAXB];
int siz[MAXN];
// dp[v][cnt]: |{ t: subtree t with root v has size cnt }|

void dfs(int v, int prv) {
    // base case
    dp[v][1] = 1;
    siz[v] = 1;
    if (v != 1 && sz(adj[v]) == 1) return;

    // inductive step
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        dfs(i, v);
        
        siz[v] += siz[i];

        memset(tmp, 0, sizeof(tmp));

        for (int p = 1; p <= min(b, siz[v]); p++) {
            if (!dp[v][p]) continue;
            for (int q = 1; p + q <= min(b, siz[v]) && q <= siz[i]; q++) {
                tmp[p + q] = (tmp[p + q] + dp[v][p] * dp[i][q]) % MOD;
            }
            tmp[p] = (tmp[p] + dp[v][p] * (dp[i][a] + dp[i][b])) % MOD;
        }

        for (int p = 1; p <= min(b, siz[v]); p++) dp[v][p] = tmp[p];
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

    dfs(1, -1);

    cout << (dp[1][a] + dp[1][b]) % MOD;
}
