// parallel binary search
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

vector<int> p;

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
    int u, v, w;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};

int n, m, qcnt;
vector<Edge> e;
vector<pii> q;

int l[101010], r[101010];
int ans2[101010];

void input() {
    cin >> n >> m;
    e.resize(m);
    for (auto& i : e) 
        cin >> i.u >> i.v >> i.w;

    cin >> qcnt;
    q.resize(qcnt);
    for (auto& i : q)
        cin >> i.fr >> i.sc;
}

void init() {
    for (int i = 0; i < qcnt; i++) {
        r[i] = m;
        ans2[i] = INF;
    }
}

void pbs() {
    while (1) {
        vector<pii> a;
        for (int i = 0; i < qcnt; i++) {
            if (l[i] == r[i]) continue;
            int mid = (l[i] + r[i]) >> 1;
            a.push_back({ mid, i });
        }

        if (a.empty()) break;

        sort(a.begin(), a.end());

        p.clear();
        p.resize(n + 1, -1);

        int idx = 0;
        for (int i = 0; i < sz(a); i++) {
            int mid = a[i].fr, qidx = a[i].sc;

            while (idx < m && idx <= mid) {
                merge(e[idx].u, e[idx].v);
                idx++;
            }

            int u = q[qidx].fr, v = q[qidx].sc;
            if (find(u) ^ find(v)) l[qidx] = mid + 1;
            else {
                ans2[qidx] = min(ans2[qidx], -p[find(u)]);
                r[qidx] = mid;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    init();

    sort(e.begin(), e.end());

    pbs();

    for (int i = 0; i < qcnt; i++) {
        if (l[i] < m) cout << e[l[i]].w << ' ' << ans2[i] << '\n';
        else cout << -1 << '\n';
    }

    return 0;
}
 
/*#define _USE_MATH_DEFINES
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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 1e5, MAXD = 16;

vector<int> p(MAX + 1, -1);

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

struct xtidx {
    int x, t, idx;
    bool operator<(const xtidx& rhs) const {
        return t < rhs.t;
    }
};

int n, m;
vt<pair<int, pii>> edge;
vt<pii> adj[MAX + 5];

int v[MAX + 5];
int dep[MAX + 5], par[MAX + 5][MAXD + 5];
int w[MAX + 5][MAXD + 5];

vt<xtidx> Q;
pii ans[MAX + 5];

void dfs(int now, int prv, int c) {
    v[now] = 1;
	par[now][0] = prv;
    w[now][0] = c;
	dep[now] = dep[prv] + 1;

	for (auto& i : adj[now]) {
		if (i.sc == prv) continue;
		dfs(i.sc, now, i.fr);
	}
}

int lca(int u, int v) {
    int ret = 0;
	if (dep[u] < dep[v]) swap(u, v);

	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) { ret = max(ret, w[u][i]); u = par[u][i]; }

	if (u == v) return ret;

	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
            ret = max(ret, w[u][i]);
            ret = max(ret, w[v][i]);
			u = par[u][i];
			v = par[v][i];
		}
	}
	return ret = max({ ret, w[u][0], w[v][0] });
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

    // input
	cin >> n >> m;
    FOR(m) {
        int u, v, w;
        cin >> u >> v >> w;
        edge.push_back({ w, { u, v } });
    }

    // making mst 
    sort(all(edge));

    EACH(i, edge) {
        int u = i.sc.fr, v = i.sc.sc, w = i.fr;
        if (find(u) != find(v)) {
            adj[u].push_back({ w, v });
            adj[v].push_back({ w, u });
            merge(u, v);
        }
    }

    // making sparse table
    FOR(i, 1, n + 1){
        if (!v[i]) dfs(i, 0, 0); 
    }

    for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
            w[v][i] = max(w[par[v][i - 1]][i - 1], w[v][i - 1]);
		}
	}

    // finding minimum temperature using lca
    int q; cin >> q;

    FOR(q) {
        int u, v;
        cin >> u >> v;

        if (find(u) != find(v)) {
            Q.push_back({ u, -1, i + 1 });
            continue;
        }

        Q.push_back({ u, lca(u, v), i + 1 });
    }

    // counting vertices using offline query
    sort(all(Q));

    p.clear();
    p.resize(MAX + 1, -1);

    int idx = 0;
    EACH(i, Q) {
        while (idx < m && edge[idx].fr <= i.t) {
            merge(edge[idx].sc.fr, edge[idx].sc.sc);
            idx++;
        }

        ans[i.idx] = { i.t, -p[find(i.x)] };
    }

    // print answer
    FOR(i, 1, q + 1) {
        if (ans[i].fr < 0) cout << ans[i].fr << '\n';
        else cout << ans[i].fr << ' ' << ans[i].sc << '\n';
    }

	return 0;
}*/