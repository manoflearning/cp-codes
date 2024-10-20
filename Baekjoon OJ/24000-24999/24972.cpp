#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

vector<int> uf(101010, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] = V;
}

int n, m, brain[101010];
set<int> adj[101010], radj[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        radj[v].insert(u);
    }
    
    // topologial sort for erasing nodes with 0 outgoing edge.
    queue<int> q;
    for (int v = 1; v <= n; v++) {
        if (adj[v].empty()) q.push(v);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        brain[v] = 1;
        for (auto& i : radj[v]) {
            adj[i].erase(v);
            if (adj[i].empty()) q.push(i);
        }
        radj[v].clear();
    }

    // now all nodes have at least 1 outgoing edge
    for (int v = 1; v <= n; v++) {
        if (sz(adj[v]) == 1)
            q.push(v);
    }

    while (sz(q)) {
        int v = q.front();
        q.pop();

        int u = *adj[v].begin();
        if (find(u) == find(v)) continue;

        merge(v, u);
        
        if (sz(radj[v]) > sz(radj[u])) swap(v, u);

        for (auto& i : radj[v]) {
            adj[i].erase(v);
            adj[i].insert(u);
            radj[u].insert(i);
            if (sz(adj[i])) q.push(i);
        }
        radj[v].clear();
        adj[v].clear();
        if (radj[u].count(v)) 
            radj[u].erase(v);

        if (sz(adj[u])) 
            pq.insert({ sz(adj[u]), u });
    }

    // query
    int m; cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        if (find(u) == find(v) || brain[u] || brain[v]) cout << 'B';
        else cout << 'H';
    }
}