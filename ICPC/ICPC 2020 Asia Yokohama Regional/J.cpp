#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 202020;

int n, m;
vector<int> adj[MAXN], t[MAXN];
int a[MAXN], cnt0[MAXN];
int dp[MAXN][2];

void input() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        a[x] = 1;
    }
}

void dfs(int v, int prv) {
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        t[v].push_back(i);
        if (a[i] == 0) cnt0[v]++;
        dfs(i, v);
    }
    adj[v].clear();
} 

int f0(int v);
int f1(int v);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, 0);

    cout << f0(1);
}

int f0(int v) {
    int ret = 1;
    for (auto& i : t[v]) {
        if (a[i] == 0) ret += f0(i);
        if (a[i] == 1) ret += f1(i);
    }
    return ret;
}

int f1(int v) {
    if (sz(t[v]) == 0 || cnt0[v] == 0) return 0;

    int ret = 1;
    
    if (cnt0[v] >= 2) {
        for (auto& i : t[v]) {
            if (a[i] == 0) ret += f0(i);
            if (a[i] == 1) ret += f1(i);
        }
    }
    else if (cnt0[v] == 1) {
        for (auto& i : t[v]) ret += f1(i);
    }

    return ret;
}
