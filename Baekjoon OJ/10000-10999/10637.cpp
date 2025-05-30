#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;
const int MAX = 101010;

vector<int> p(MAX, -1);

int find(int x) { 
    if (p[x] < 0) return x; 
    return p[x] = find(p[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    p[U] += p[V];
    p[V] = U;
}

struct Edge { 
    int w, u, v, idx; 
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};

int n, m, edgeVisited[MAX << 1];
vector<Edge> edge;
vector<int> adj[MAX];
ll wsum = 0;

void input() {
    cin >> n >> m;
    edge.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edge[i].u >> edge[i].v;
        cin >> edge[i].w;
        edge[i].idx = i;
    }
}

void buildMST() {
    vector<Edge> e2 = edge;

    sort(e2.begin(), e2.end());

    for (auto& i : e2) {
        if (find(i.u) == find(i.v)) continue;
        edgeVisited[i.idx] = 1;
        wsum += i.w;
        adj[i.u].push_back(i.v);
        adj[i.v].push_back(i.u);
        merge(i.u, i.v);
    }
}

vector<int> t[MAX];
bool visited[MAX];
int siz[MAX], dep[MAX], par[MAX]; 
int top[MAX], in[MAX], pv;

void dfs(int v) {
    visited[v] = 1;
    for (auto& i : adj[v]) {
        if (visited[i]) continue;
        t[v].push_back(i);
        dfs(i);
    }
}

void dfs1(int v) {
    visited[v] = 1;
    siz[v] = 1;
    for (auto& i : t[v]) {
        dep[i] = dep[v] + 1, par[i] = v;
        dfs1(i);
        siz[v] += siz[i];
        if (siz[i] > siz[t[v][0]]) swap(i, t[v][0]);
    }
}

void dfs2(int v) {
    visited[v] = 1;
    in[v] = ++pv;
    for (auto& i : t[v]) {
        top[i] = (i == t[v][0] ? top[v] : i);
        dfs2(i);
    }
}

void buildHLD() {
    for (int v = 1; v <= n; v++) {
        if (!visited[v]) dfs(v);
    }

    memset(visited, 0, sizeof(visited));

    for (int v = 1; v <= n; v++) {
        if (!visited[v]) dfs1(v);
    }

    memset(visited, 0, sizeof(visited));

    for (int v = 1; v <= n; v++) {
        if (!visited[v]) dfs2(v);
    }
}

int flag;  // array size
struct Seg {  // 1-indexed
	vector<int> t, lazy;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, INF);
		lazy.resize(2 * flag, INF);
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, int value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);

		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] = min(value, lazy[n]);
			propagate(n, nl, nr);
			return;
		}

		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);

		t[n] = min(t[n << 1], t[n << 1 | 1]);
	}
	int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);

		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != INF) {
			if (n < flag) {
				lazy[n << 1] = min(lazy[n << 1], lazy[n]);
				lazy[n << 1 | 1] = min(lazy[n << 1 | 1], lazy[n]);
			}
			t[n] = min(t[n], lazy[n]);
			lazy[n] = INF;
		}
	}
}seg;

void modify(int u, int v, ll w) {
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        seg.modify(in[st], in[u], w);
        u = par[st];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.modify(in[u] + 1, in[v], w);
}

int query(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    return seg.query(in[u], in[u]);
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildMST();

    buildHLD();

    seg.build(pv);
    
    for (auto& i : edge) {
        if (edgeVisited[i.idx]) continue;
        modify(i.u, i.v, i.w);
    }

    for (auto& i : edge) {
        if (edgeVisited[i.idx]) {
            ll res = query(i.u, i.v);
            
            if (res == INF) cout << -1 << '\n';
            else cout << wsum - i.w + res << '\n';
        }
        else cout << wsum << '\n';
    }

    return 0;
}