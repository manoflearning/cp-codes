#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int MAXN = 505050;
const int MAXD = 18;
const ll INF = 1e18;

int n, q;
vector<pli> adj[MAXN];

bool used[MAXN];
int siz[MAXN];

int cdpar[MAXN];
ll cddist[MAXN][22];

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
		for (int v = 0; v < n; v++) {
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
        if (used[i.sc] || i.sc == prv) continue;
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

    cdpar[cent] = prv;

    used[cent] = 1;
    for (auto& i : adj[cent]) {
        if (!used[i.sc]) cd(i.sc, cent);
    }
}

vector<ll> xmin(MAXN, INF);
void solve() {
    int s, t;
    cin >> s >> t;

    vector<int> x(s), y(t);
    for (auto& i : x) cin >> i;
    for (auto& i : y) cin >> i;

    for (auto& i : x) {
        int cnt = 0;
        for (int v = i; v != n; v = cdpar[v]) {
            xmin[v] = min(xmin[v], cddist[i][cnt]);
            cnt++;
        }
    }

    ll ans = INF;
    for (auto& i : y) {
        int cnt = 0;
        for (int v = i; v != n; v = cdpar[v]) {
            ans = min(ans, cddist[i][cnt] + xmin[v]);
            cnt++;
        }
    }

    for (auto& i : x) {
        for (int v = i; v != n; v = cdpar[v]) {
            xmin[v] = INF;
        }
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

    for (int v = 0; v < n; v++) {
        for (int p = v, i = 0; p != n; p = cdpar[p], i++) {
            cddist[v][i] = get_dist(p, v);
        }
    }

    while (q--) solve();
}
