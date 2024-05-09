#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<int> adj[303030];
ll sum[303030], cnt[303030], dist_1[303030], ans = 0;

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    if (v == 1) dist_1[v] = 0;
    else dist_1[v] = dist_1[prv] + 1;

    for (auto& i : adj[v]) {
        if (i == prv) continue;
        dfs(i, v);
        sum[v] += sum[i] + cnt[i];
        cnt[v] += cnt[i];
    }
    cnt[v]++;

    // hit the root node 1
    ll pcnt = 0;
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        ans += cnt[i] * pcnt * dist_1[v];
        pcnt += cnt[i];
    }
    ans += (cnt[v] - 1) * dist_1[v];

    // between all the pairs
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        ans += (sum[i] + cnt[i]) * (cnt[v] - cnt[i]);
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

    cout << ans;
}