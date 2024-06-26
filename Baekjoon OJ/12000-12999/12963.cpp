#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

int n, m;
struct Edge { int w, v; };
vector<Edge> adj[2020];
ll p3[2020], ans;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        adj[u].push_back({ i, v });
        adj[v].push_back({ i, u });
    }
}

int vi[2020], banned[2020];
int dfs(int v, int lb) {
    if (v == n) return 1;
    int ret = 0;
    vi[v] = 1;
    for (auto& i : adj[v]) {
        if (i.w < lb || banned[i.w] || vi[i.v]) continue;
        ret |= dfs(i.v, lb);
    }
    return ret;
}

void solve() {
    p3[0] = 1;
    for (int i = 1; i < 2020; i++)
        p3[i] = 3 * p3[i - 1] % MOD;
    
    for (int i = m - 1; i >= 0; i--) {
        memset(vi, 0, sizeof(vi));
        if (dfs(1, i)) {
            ans = (ans + p3[i]) % MOD;
            banned[i] = 1;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}