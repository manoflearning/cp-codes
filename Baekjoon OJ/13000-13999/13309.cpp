#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXV = 202020;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p) {  // set value at position p
		for (t[p += flag - 1]++; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int n, q;
vector<int> adj[MAXV], g[MAXV];
int siz[MAXV], dep[MAXV], par[MAXV];
int top[MAXV], in[MAXV], pv;

void input() {
    cin >> n >> q;
    for (int v = 2; v <= n; v++) {
        int u; cin >> u;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
}

void dfs(int v, int prv) {
	for (auto& i : adj[v]) {
		if (i == prv) continue;
		g[v].push_back(i);
		dfs(i, v);
	}
}

int dfs1(int v) {
	siz[v] = 1;
	for (auto& i : g[v]) {
		dep[i] = dep[v] + 1, par[i] = v;
		siz[v] += dfs1(i);
		if (siz[i] > siz[g[v][0]]) swap(i, g[v][0]);
	}
	return siz[v];
}

void dfs2(int v) {
	in[v] = ++pv;
	for (auto& i : g[v]) {
		top[i] = (i == g[v][0] ? top[v] : i);
		dfs2(i);
	}
}

void modify(int v) {
	seg.modify(in[v]);
}

ll query(int u, int v) {
	ll ret = 0;
	while (top[u] ^ top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		int st = top[u];
		ret += seg.query(in[st], in[u]);
		u = par[st];
	}
	if (dep[u] > dep[v]) swap(u, v);
	ret += seg.query(in[u] + 1, in[v]);
    
	return ret;
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
	top[1] = 1;
	dfs1(1); 
	dfs2(1);

    seg.build(pv);

	while (q--) {
		int u, v, op;
        cin >> u >> v >> op;

        if (!query(u, v)) {
            cout << "YES\n";
            if (op == 1) modify(u);
        }
        else {
            cout << "NO\n";
            if (op == 1) modify(v);
        }
	}

	return 0;
}