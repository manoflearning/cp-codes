#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 5050;
const int MAXB = 5050;

int n, b;
bool isb[MAXN];
vector<int> adj[MAXN];

void input() {
    cin >> n >> b;
    for (int i = 0; i < b; i++) {
        int x; cin >> x;
        isb[x] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int siz[MAXN];
vector<int> dp[MAXN][MAXN];
// ll dp[MAXN][MAXB];

void dfs(int v, int prv) {
    dp[v][1].push_back(isb[v]);
    siz[v] = 1;

    // dp[1][isb[v]] = 1;

    for (auto& u : adj[v]) {
        if (u == prv) continue;
        dfs(u, v);
        
        for (int i = 0; i <= siz[v]; i++) {
            for (int j = 0; j <= siz[u]; j++) {
                
            }
        }
        siz[v] += siz[u];
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

    int q; cin >> q;
    while (q--) {

    }
}
