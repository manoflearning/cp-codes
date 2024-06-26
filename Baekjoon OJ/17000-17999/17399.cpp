#include <bits/stdc++.h>
using namespace std;

const int MAX = 101010, MAXD = 16;  // 2^MAXD = 65536

vector<int> adj[MAX];
int n, dep[MAX], par[MAX][MAXD + 1];

void input() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void dfs(int now, int prv) {
	par[now][0] = prv;
	dep[now] = dep[prv] + 1;
	for (auto i : adj[now]) {
		if (i == prv) continue;
		dfs(i, now);
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

    int ret = diff;

	if (u == v) return ret;

	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
            ret += 2 * (1 << i);
		}
	}
	
	return ret + 2;
}

int lca2(int u, int v) {
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

int goup(int v, int len) {
    for (int i = MAXD; i >= 0; i--) {
        if (len & (1 << i)) v = par[v][i];
    }
    return v;
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

    buildSparseTable();

    int q; cin >> q;
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;

        if (x == y && y == z) cout << x << '\n';
        else if (x == y || y == z || z == x) {
            if (x == y) y = z;
            int len = lca(x, y);

            if (len & 1) cout << -1 << '\n';
            else {
                if (dep[x] < dep[y]) swap(x, y);
                cout << goup(x, len / 2) << '\n';
            }
        }
        else {
            int xy = lca(x, y), yz = lca(y, z), zx = lca(z, x);

            if ((xy & 1) || (yz & 1) || (zx & 1)) cout << -1 << '\n';
            else {
                int u, v;
                if (xy >= yz && xy >= zx) u = x, v = y;
                else if (yz >= xy && yz >= zx) u = y, v = z;
                else if (zx >= xy && zx >= yz) u = z, v = x;

                if (dep[u] < dep[v]) swap(u, v);

                int len = lca(u, v), m = goup(u, len / 2);
                int xm = lca(x, m), ym = lca(y, m), zm = lca(z, m);
                
                if (xm == len / 2 && ym == len / 2 && zm == len / 2) cout << m << '\n';
                else cout << -1 << '\n';
            }
        }
    }
    
    return 0;
}