#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n, m, a[101010];
vector<int> adj[101010];
ll ans = 0;

bool vis[101010], used[101010];
pair<int, int> dfs(int v) {
    pair<int, int> ret = {a[v], v};
    vis[v] = 1;
    for (auto &i : adj[v]) {
        if (!vis[i]) ret = min(ret, dfs(i));
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (m == n - 1) {
        cout << 0;
        exit(0);
    }

    int ccnt = n - m, vcnt = 2 * (ccnt - 1);
    for (int v = 0; v < n; v++) {
        if (vis[v]) continue;
        auto res = dfs(v);
        used[res.second] = 1;
        ans += res.first;
        vcnt--;
    }
    
    vector<int> arr;
    for (int v = 0; v < n; v++) {
        if (!used[v]) arr.push_back(a[v]);
    }

    sort(all(arr));

    if (sz(arr) < vcnt) {
        cout << "Impossible";
        exit(0);
    }

    for (int i = 0; i < vcnt; i++) ans += arr[i];

    cout << ans;
}
