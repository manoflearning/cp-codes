#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 2020, MAXD = 12;
const ll INF = 1e18;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, INF);
		lazy.resize(2 * flag, INF);
		// for (int i = flag; i < flag + n; i++) cin >> t[i];
		// for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] = min(lazy[n], value);
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = min(t[n << 1], t[n << 1 | 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
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

int n, m, a, b;
struct Edge { ll w; int v; };
vector<Edge> adj[MAXN];

int k;
int v[MAXN], rv[MAXN];

void input() {
    cin >> n >> m >> a >> b;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> v[i];
        rv[v[i]] = i;
    }
}

vector<ll> dist_fw(MAXN, INF), dist_bw(MAXN, INF);

void dijkstra(int st, int en, vector<ll>& dist) {
    priority_queue<pair<ll, int>> pq;
    dist[st] = 0;
    pq.push({ -dist[st], st });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        w *= -1;

        if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            if (dist[i.v] <= w + i.w) continue;
            dist[i.v] = w + i.w;
            pq.push({ -dist[i.v], i.v });
        }
    }
}

vector<vector<int>> t_fw(MAXN), t_bw(MAXN);
vector<bool> vis_fw(MAXN), vis_bw(MAXN);
vector<int> par_fw(MAXN), par_bw(MAXN);

void dfs(int v, int prv, const vector<ll>& dist, vector<vector<int>>& t, vector<bool>& vis, vector<int>& par) {
    vis[v] = 1;
    par[v] = (rv[v] ? v : par[prv]);

    for (auto& i : adj[v]) {
        if (dist[v] + i.w != dist[i.v]) continue;
        if (!rv[v] || !rv[i.v]) continue;
        t[v].push_back(i.v);
        dfs(i.v, v, dist, t, vis, par);
    }

    for (auto& i : adj[v]) {
        if (dist[v] + i.w != dist[i.v]) continue;
        if (vis[i.v]) continue;
        t[v].push_back(i.v);
        dfs(i.v, v, dist, t, vis, par);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dijkstra(a, b, dist_fw);
    dijkstra(b, a, dist_bw);

    dfs(a, 0, dist_fw, t_fw, vis_fw, par_fw);
    dfs(b, 0, dist_bw, t_bw, vis_bw, par_bw);

    seg.build(n);
    for (int v = 1; v <= n; v++) {
        for (auto& i : adj[v]) {
            if (rv[v] && rv[i.v] && rv[v] + 1 == rv[i.v]) continue;
            int l = rv[par_fw[v]];
            int r = rv[par_bw[i.v]] - 1;
            ll val = dist_fw[v] + i.w + dist_bw[i.v];
            seg.modify(l, r, val);
        }
    }

    for (int i = 1; i + 1 <= k; i++) {
        ll res = seg.query(i, i);
        cout << (res == INF ? -1 : res) << '\n';
    }
}
