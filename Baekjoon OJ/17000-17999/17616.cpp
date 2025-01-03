#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;

int n, m, st;
vector<int> adj1[MAXN], adj2[MAXN];

void input() {
    cin >> n >> m >> st;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
        adj2[v].push_back(u);
    }
}

int vi[MAXN];
int dfs(int v, int bit) {
    int ret = 1;
    vi[v] = 1;
    if (bit) for (auto& i : adj1[v]) { if (!vi[i]) ret += dfs(i, bit); }
    else for (auto& i : adj2[v]) { if (!vi[i]) ret += dfs(i, bit); }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cout << dfs(st, 0) << ' ';
    memset(vi, 0, sizeof(vi));
    cout << n - dfs(st, 1) + 1;
}