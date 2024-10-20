#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, qu, deg[202020], vi[202020], cnt;
vector<int> adj[202020];

void dfs(int v) {
    vi[v] = cnt;
    for (auto& i : adj[v]) {
        if (deg[i] == 2) continue;
        if (vi[i]) continue;
        dfs(i);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> qu;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }

    queue<int> q;

    for (int v = 1; v <= n; v++) {
        if (deg[v] == 1) {
            q.push(v);
        } 
    }

    while (sz(q)) {
        int v = q.front();
        q.pop();

        vi[v] = 1;

        for (auto& i : adj[v]) {
            if (vi[i]) continue;
            
            deg[i]--;
            if (deg[i] == 1) q.push(i);
        }
    }

    memset(vi, 0, sizeof(vi));

    for (int v = 1; v <= n; v++) {
        if (deg[v] == 2) {
            cnt++;
            dfs(v);
        }
    }

    while (qu--) {
        int u, v;
        cin >> u >> v;

        if (vi[u] == vi[v]) cout << 1 << '\n';
        else cout << 2 << '\n';
    }

    return 0;
}