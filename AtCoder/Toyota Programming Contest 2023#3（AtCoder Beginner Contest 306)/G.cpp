//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXV = 202020;

int n, m;
vector<int> adj[MAXV], radj[MAXV];
int in[MAXV], out[MAXV], num, p[2 * MAXV];
int vi[MAXV], cnt;
vector<vector<int>> scc;

int canGo[MAXV];
vector<int> adj2[MAXV];

void init() {
    num = cnt = 0;
    scc.clear();
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        radj[i].clear();
        in[i] = out[i] = p[i << 1] = p[i << 1 | 1] = 0;
        vi[i] = 0; 
        canGo[i] = 0;
        adj2[i].clear();
    }
    n = m = 0;
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
}

void dfs(int v) {
    in[v] = ++num;
    for (auto& i : radj[v]) {
        if (!in[i]) dfs(i);
    }
    out[v] = ++num;
    p[num] = v;
}

void flood(int v) {
    scc[cnt].push_back(v);
    vi[v] = cnt;
    for (auto& i : adj[v]) {
        if (!vi[i]) flood(i);
    }
}

void kosaraju() {
    for (int v = 1; v <= n; v++) {
        if (!in[v]) dfs(v);
    }
    for (int v = 2 * n; v >= 1; v--) {
        if (!p[v]) continue;
        if (vi[p[v]]) continue;
        cnt++;
        scc.resize(cnt + 1);
        flood(p[v]);
    }
}

int bfs(const vector<int>& arr) {
    vector<int> dist(n + 1, -1);

	queue<int> q;
    dist[1] = 0;
    q.push(1);
    
    int ret = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        ret = max(ret, 1 + dist[v]);

        for (auto& i : adj2[v]) {
            if (dist[i] == -1) {
                dist[i] = dist[v] + 1;
                q.push(i);
            }
        }
    }

    for (auto& v : arr) {
        for (auto& u : adj2[v]) {
            if (u != 1 && (dist[v] + 1) != dist[u]) {
                return -1;
            }
        }
    }

    return ret;
}

int solve() {
    vector<int> arr = scc[vi[1]];
    for (auto& i : arr) canGo[i] = 1;

    for (auto& v : arr) {
        for (auto& u : adj[v])
            if (canGo[u]) adj2[v].push_back(u);
    }
    
    int res = bfs(arr);
    
    if (res == -1) return 1;

    while (res % 2 == 0) res /= 2;
    while (res % 5 == 0) res /= 5;
    return res == 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        input();

        kosaraju();

        cout << (solve() ? "Yes" : "No") << '\n';

        init();
    }
}