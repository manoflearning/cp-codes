#define _USE_MATH_DEFINES
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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const ll INF = 1e15;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

vector<int> p(50505, -1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}

struct Edge {
    int v, u;
    ll w;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};

int n, m, vi[202020];
vt<Edge> adj[50505], edge;

void input() {
    cin >> n >> m;
    FOR(m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, u, w });
        adj[v].push_back({ u, v, w });
        edge.push_back({ u, v, w });
    }
}

void dfs1(int v) {
    vi[v] = 1;
    EACH(i, adj[v]) {
        if (!vi[i.v]) dfs1(i.v);
    }
}

const int D = 16;

vt<Edge> t[50505];
int dep[50505], par[50505][D + 1];
pll mx[50505][D + 1];

void init() {
    FOR(50505) FOR(j, D + 1) mx[i][j] = { -1, -1 };
}

void dfs2(int v, int prv) {
    dep[v] = dep[prv] + 1;
    par[v][0] = prv;
    EACH(i, t[v]) {
        if (i.v == prv) continue;
        mx[i.v][0] = { i.w, -1 };
        dfs2(i.v, v);
    }
}

void buildSparseTable() {
    for (int i = 1; i <= D; i++) {
        for (int v = 1; v <= n; v++) {
            par[v][i] = par[par[v][i - 1]][i - 1];

            vt<ll> a;
            a.push_back(mx[v][i - 1].fr);
            a.push_back(mx[v][i - 1].sc);
            a.push_back(mx[par[v][i - 1]][i - 1].fr);
            a.push_back(mx[par[v][i - 1]][i - 1].sc);
            
            sort(a.rbegin(), a.rend());
            a.erase(unique(all(a)), a.end());
            mx[v][i].fr = a[0], mx[v][i].sc = a[1];
            //cout << i << ' ' << j << ' ' << a[0] << ' ' << a[1] << '\n';
        }
    }
}

pll lca(int u, int v) {
    priority_queue<ll> ret; ret.push(-1);
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int i = D; i >= 0; i--) {
        if (diff & (1 << i)) {
            ret.push(mx[u][i].fr);
            ret.push(mx[u][i].sc);
            u = par[u][i];
        }
    }

    if (u == v) {
        ll x = ret.top(); ret.pop();
        while (sz(ret) && x == ret.top()) ret.pop();
        return { x, (sz(ret) ? ret.top() : -1) };
    }

    for (int i = D; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            ret.push(mx[u][i].fr);
            ret.push(mx[u][i].sc);
            ret.push(mx[v][i].fr);
            ret.push(mx[v][i].sc);
            u = par[u][i];
            v = par[v][i];
        }
    }
    ret.push(mx[u][0].fr);
    ret.push(mx[u][0].sc);
    ret.push(mx[v][0].fr);
    ret.push(mx[v][0].sc);

    ll x = ret.top(); ret.pop();
    while (sz(ret) && x == ret.top()) ret.pop();
    return { x, (sz(ret) ? ret.top() : -1) };
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

	input();

    if (n == 1) {
        cout << -1;
        return 0;
    }

    int cCnt = 0;
    FOR(i, 1, n + 1) {
        if (!vi[i]) { dfs1(i); cCnt++; }
    }

    if (cCnt >= 2) {
        cout << -1;
        return 0;
    }

    sort(all(edge));

    memset(vi, 0, sizeof(vi));
    ll mstCost = 0;
    FOR(m) {
        auto& e = edge[i];
        if (find(e.u) == find(e.v)) continue;
        mstCost += e.w;
        merge(e.u, e.v);
        vi[i] = 1;
        t[e.u].push_back({ e.v, e.u, e.w });
        t[e.v].push_back({ e.u, e.v, e.w });
        //cout << e.v << ' ' << e.u << ' ' << e.w << '\n';
    }
    
    dfs2(1, 0);
    
    buildSparseTable();

    ll ans = INF;
    FOR(m) {
        if (vi[i]) continue;
        pll res = lca(edge[i].u, edge[i].v);
        //cout << edge[i].u << ' ' << edge[i].v << ' ' << res.fr << ' ' << res.sc << '\n';
        if (res.fr != -1 && res.fr != edge[i].w) ans = min(ans, mstCost + edge[i].w - res.fr);
        else if (res.sc != -1 && res.sc != edge[i].w) ans = min(ans, mstCost + edge[i].w - res.sc);
    }
    
    if (ans == INF) cout << -1;
    else cout << ans;

	return 0;
}