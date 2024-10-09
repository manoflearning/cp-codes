#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define fr first
#define sc second

const int MAXN = 505050;
const int MAXD = 20;
const ll INF = 1e18;

int n, q;
vector<pli> adj[MAXN];

bool used[MAXN];
int siz[MAXN];

int cdpar[MAXN];
vector<int> cdchd[MAXN];
ll cddist[MAXN];
int cddep[MAXN];
vector<int> cdbydep[21];

int s, t;
vector<int> x, y;

void input() {
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

int dep[MAXN], par[MAXN][MAXD + 1];
ll dist[MAXN][MAXD + 1];
void dfs(int now, int prv) {
	par[now][0] = prv;
	dep[now] = dep[prv] + 1;
	for (auto i : adj[now]) {
		if (i.sc == prv) continue;
        dist[i.sc][0] = i.fr;
		dfs(i.sc, now);
	}
}
void buildSparseTable() {
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
            dist[v][i] = dist[v][i - 1] + dist[par[v][i - 1]][i - 1];
		}
	}
}
ll get_dist(int u, int v) {
    ll ret = 0;

    if (dep[u] < dep[v]) swap(u, v);
	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) {
            ret += dist[u][i];
            u = par[u][i];
        }
	if (u == v) return ret;
	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
            ret += dist[u][i];
            ret += dist[v][i];
			u = par[u][i];
			v = par[v][i];
		}
	}
	return ret + dist[u][0] + dist[v][0];
}

int get_size(int now, int prv) {
    siz[now] = 1;
    for (auto& i : adj[now]) {
        if (used[i.sc] || prv == i.sc) continue;
        siz[now] += get_size(i.sc, now);
    }
    return siz[now];
}
int get_cent(int now, int prv, int mxsiz) {
    for (auto& i : adj[now]) {
        if (used[i.sc] || i.sc == prv) continue;
        if (siz[i.sc] > mxsiz / 2) return get_cent(i.sc, now, mxsiz);
    }
    return now;
}

void cd(int now, int prv) {
    int mxsiz = get_size(now, prv);
    int cent = get_cent(now, prv, mxsiz);

    cdchd[prv].push_back(cent);
    cdpar[cent] = prv;
    cddep[cent] = 1 + cddep[prv];
    cdbydep[cddep[cent]].push_back(cent);
    cddist[cent] = (prv == n ? 0 : get_dist(cent, prv));

    used[cent] = 1;
    for (auto& i : adj[cent]) {
        if (!used[i.sc]) cd(i.sc, cent);
    }
}

vector<ll> xmin(MAXN, INF), ymin(MAXN, INF);
vector<bool> vis(MAXN);

void solve() {
    cin >> s >> t;
    x.resize(s);
    y.resize(t);
    for (auto& i : x) cin >> i;
    for (auto& i : y) cin >> i;

    priority_queue<pii> pq;

    for (auto& i : x) {
        xmin[i] = 0;
        if (!vis[i]) {
            vis[i] = 1;
            pq.push({ cddep[i], i });
        }
    }
    for (auto& i : y) {
        ymin[i] = 0;
        if (!vis[i]) {
            vis[i] = 1;
            pq.push({ cddep[i], i });
        }
    }

    vector<int> lazy_init;

    ll ans = INF;
    while (!pq.empty()) {
        auto [_, v] = pq.top();
        pq.pop();

        lazy_init.push_back(v);

        ans = min(ans, ymin[v] + xmin[v]);

        int p = cdpar[v];
        ymin[p] = min(ymin[p], ymin[v] + cddist[v]);
        xmin[p] = min(xmin[p], xmin[v] + cddist[v]);

        if (!vis[p]) {
            vis[p] = 1;
            pq.push({ cddep[p], p });
        }
    }

    for (auto& i : lazy_init) {
        ymin[i] = xmin[i] = INF;
        vis[i] = 0;
    }

    cout << ans << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(0, n);
    buildSparseTable();

    cd(0, n);

    while (q--) solve();
}
