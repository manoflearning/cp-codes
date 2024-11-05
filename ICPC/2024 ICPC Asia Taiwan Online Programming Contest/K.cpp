#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n, m, ind[101010];
vector<int> adj[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        ind[v]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int v = 1; v <= n; v++) 
        if (!ind[v]) pq.push(v);
    
    vector<int> ans;
    while (!pq.empty()) {
        int v = pq.top(); pq.pop();
        ans.push_back(v);

        for (auto &i : adj[v]) {
            ind[i]--;
            if (!ind[i]) pq.push(i);
        }
    }

    if (sz(ans) < n) cout << "IMPOSSIBLE";
    else for (auto &i : ans) cout << i << ' ';
}
