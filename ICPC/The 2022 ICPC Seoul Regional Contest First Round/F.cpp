#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m, ind[1010101], vi[1010101], w[1010101];
vector<int> adj[1010101];

void input() {
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        ind[v]++;
        adj[u].push_back(v);
    }
}

vector<int> res;

void dfs(int v) {
    vi[v] = 1;
    res.push_back(v);
    for (auto& i : adj[v]) {
        if (!vi[i]) dfs(i);
    }
}

int dp[1010101];

int f(int v) {
    int& ret = dp[v];
    if (ret != -1) return ret;
    
    ret = 1;
    for (auto& i : adj[v]) {
        if (!w[i]) ret += f(i);
        else ret += w[i];
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif
    
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

    input();

    queue<int> q;
    for (int v = 1; v <= n; v++) {
        if (!ind[v]) q.push(v);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        vi[v] = 1;

        for (auto& i : adj[v]) {
            ind[i]--;
            if (!ind[i]) q.push(i);
        }
    }

    for (int v = 1; v <= n; v++) {
        if (!vi[v]) {
            res.clear();
            dfs(v);
            for (auto& i : res) 
                w[i] = res.size();
        }
    }

    int ans = 0;
    for (int v = 1; v <= n; v++) {
        if (w[v]) ans = max(ans, w[v]);
        else ans = max(ans, f(v));
    }

    cout << ans;

    return 0;
}