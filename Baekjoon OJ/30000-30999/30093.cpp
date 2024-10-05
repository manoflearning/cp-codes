#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const ll INF = 1e18;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
	}
	void add(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] += value; p > 1; p >>= 1) 
            t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int n, m, k;
vector<int> st;
struct Edge {
    ll w; int v;
};
vector<Edge> adj[MAXN];
vector<ll> minw(MAXN, INF);

vector<ll> dist(MAXN, INF);
vector<bool> vis(MAXN);

ll ans = 0;

void input() {
    cin >> n >> m >> k;
    st.resize(m);
    for (auto& i : st) cin >> i;
    for (int i = 0; i < k; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
        minw[u] = min(minw[u], w);
        minw[v] = min(minw[v], w);
    }
}

void dijkstra() {
    priority_queue<pair<ll, int>> pq;

    for (auto& i : st) {
        dist[i] = 0;
        pq.push({ -dist[i], i });
    }

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        w *= -1;

        if (dist[v] < w) continue;
        
        for (auto& i : adj[v]) {
            if (dist[i.v] > w + i.w) {
                dist[i.v] = w + i.w;
                pq.push({ -dist[i.v], i.v });
            }
        }
    }
}

vector<ll> cc;
void value_comp() {
    cc.push_back(-INF);
    for (int v = 1; v <= n; v++) {
        cc.push_back(dist[v]);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int v = 1; v <= n; v++) {
        dist[v] = lower_bound(all(cc), dist[v]) - cc.begin();
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

    dijkstra();

    vector<int> ord(n);
    iota(all(ord), 1);

    sort(all(ord), [&](int p1, int p2) {
        return minw[p1] > minw[p2];
    });

    value_comp();
    
    seg.build(n + 1);
    for (int v : ord) {
        int lb = lower_bound(all(cc), cc[dist[v]] - minw[v]) - cc.begin();
        int ub = upper_bound(all(cc), cc[dist[v]] + minw[v]) - cc.begin();

        ans += seg.query(lb, ub - 1);
        
        for (auto& i : adj[v]) {
            if (vis[i.v] && lb <= dist[i.v] && dist[i.v] < ub) ans--;
        }
        
        seg.add(dist[v], 1);
        vis[v] = 1;
    }

    cout << ans;
}
