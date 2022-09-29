#include <bits/stdc++.h>
using namespace std;

const int MAXD = 17;

int n, q;
vector<int> adj[202020], t[202020];
int x, y, vi[202020], cy[202020];
int dep[202020], par[202020][MAXD + 1];

void input() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    par[v][0] = prv;
	dep[v] = dep[prv] + 1;
    for (auto& i : adj[v]) {
        if (i == prv) continue;

        if (!dep[i]) {
            dfs(i, v);
            t[v].push_back(i);
        }
        else x = v, y = i;
    }
}

void dfs2(int v) {
    vi[v] = 1;
    if (v == x) cy[v] = 1;
    
    for (auto& i : t[v]) {
        dfs2(i);
        if (cy[i]) cy[v] = 1;
    }
}

void buildSparseTable() {
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);

	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) u = par[u][i];

	if (u == v) return u;

	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	
	return par[u][0];
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, 0);

    dfs2(y);

    buildSparseTable();

    while (q--) {
        int u, v;
        cin >> u >> v;

        if (vi[u] && vi[v]) {
            int p = lca(u, v);
            if (p != y && p != x && cy[x]) cout << 2 << '\n';
            else cout << 1 << '\n';
        }
        else if (vi[u] || vi[v]) cout << 2 << '\n';
        else cout << 1 << '\n';
    }

    return 0;
}