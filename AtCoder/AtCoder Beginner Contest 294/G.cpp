//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXV = 202020;
int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

struct idxvw {
    int idx, v; ll w;
};

vector<idxvw> adj[MAXV], g[MAXV];
int siz[MAXV], dep[MAXV], par[MAXV];
int top[MAXV], in[MAXV], out[MAXV], pv;
int edge[MAXV], w[MAXV];

void dfs(int v, int prv) {
	for (auto& i : adj[v]) {
		if (i.v == prv) continue;
		g[v].push_back(i);
        edge[i.idx] = i.v;
		dfs(i.v, v);
	}
}
int dfs1(int v) {
	siz[v] = 1;
	for (auto& i : g[v]) {
		dep[i.v] = dep[v] + 1, par[i.v] = v;
		siz[v] += dfs1(i.v);
		if (siz[i.v] > siz[g[v][0].v]) swap(i, g[v][0]);
	}
	return siz[v];
}
void dfs2(int v) {
	in[v] = ++pv;
	for (auto& i : g[v]) {
		top[i.v] = (i.v == g[v][0].v ? top[v] : i.v);
		dfs2(i.v);
	}
	out[v] = pv;
}
void modify(int v, ll value) {
	seg.modify(in[v], value);
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

int n, q;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v >> w[i + 1];
        adj[u].push_back({ i + 1, v, w[i + 1] });
        adj[v].push_back({ i + 1, u, w[i + 1] });
    }

    dfs(1, 0);
	top[1] = 1;
	dfs1(1); 
	dfs2(1);

    seg.build(pv);
    for (int i = 1; i < n; i++) {
        modify(edge[i], w[i]);
    }

    cin >> q;
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) modify(edge[x], y);
        if (op == 2) cout << query(x, y) << '\n';
    }

	return 0;
}