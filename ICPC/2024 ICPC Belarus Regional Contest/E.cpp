#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, a[101010];
vector<int> adj[101010];

vector<int> ans;

void dfs(int v, int prv) {
    ans.push_back(v);
    a[v]--;

    for (auto &i : adj[v]) {
        if (i != prv) {
            dfs(i, v);
            a[v]--;
            ans.push_back(v);
        }
    }

    for (auto &i : adj[v]) {
        if (i != prv) {
            if (a[i] > 0 && a[v] > 0) {
                int cap = min(a[i], a[v]);
                a[i] -= cap;
                a[v] -= cap;
                while (cap--) {
                    ans.push_back(i);
                    ans.push_back(v);
                }
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    a[1]++;
    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        if (a[i]) { cout << 0; exit(0); }
    }
    
    for (auto &i : ans) cout << i << ' ';
}
