// 임의의 마을 v는 최대 1개의 고행의 길로 도달 가능하거나, 도달 가능하지 않다.

// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 202020;

int N, M;
ll h[MAXN], H[MAXN];
ll p[MAXN];
struct Edge {
    ll w; int v;
    bool operator<(const Edge& rhs) const {
        return w > rhs.w;
    }
};
vector<Edge> adj[MAXN];

ll dist[2][MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) 
        dist[0][i] = dist[1][i] = INF;
}

void input() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> h[i];
    for (int i = 1; i <= N; i++) cin >> p[i];
    for (int i = 0; i < M; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        adj[u].push_back({ t, v });
    }
}

void dijkstra0() {
    priority_queue<Edge> pq;
    pq.push({ 0, 1 });
    dist[0][1] = 0;

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (w > dist[0][v]) continue;

        for (auto& i : adj[v]) {
            if (dist[0][i.v] > w + i.w) {
                dist[0][i.v] = w + i.w;
                pq.push({ w + i.w, i.v });
            }
        }
    }
}

void buildH() {
    for (int v = 1; v <= N; v++) {
        H[v] = h[v];
        for (auto& i : adj[v]) {
            H[v] = max(H[v], h[i.v]);
        }
    }
}

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

void pathp() {
    // build ord
    vector<int> ordH, ordh;
    ordH.push_back(0);
    ordh.push_back(0);
    for (int v = 1; v <= N; v++) {
        ordH.push_back(v);
        ordh.push_back(v);
    }
    
    sort(all(ordH), [&](int p1, int p2) {
        return H[p1] < H[p2];
    });
    sort(all(ordh), [&](int p1, int p2) {
        return h[p1] < h[p2];
    });

    // build segment tree
    seg.build(N);
    for (int i = 1; i <= N; i++) {
        seg.modify(i, i, dist[0][ordh[i]]);
    }

    // solve
    int lb = 1;
    for (int i = 1; i <= N; i++) {
        int v = ordH[i];
        while (lb <= N && H[v] >= h[ordh[lb]]) lb++;
        if (dist[0][v] == INF) continue;
        seg.modify(lb, N, dist[0][v] + p[v]);
    }

    // build dist1
    for (int i = 1; i <= N; i++) {
        dist[1][ordh[i]] = seg.query(i, i);
    }
}


void dijkstra1() {
    priority_queue<Edge> pq;
    for (int v = 1; v <= N; v++) {
        if (dist[1][v] != INF) pq.push({ dist[1][v], v });
    }

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (w > dist[1][v]) continue;
        
        for (auto& i : adj[v]) {
            if (dist[1][i.v] > w + i.w) {
                dist[1][i.v] = w + i.w;
                pq.push({ w + i.w, i.v });
            }
        }
    }
}

void output() {
    ll ans = 0;
    for (int v = 1; v <= N; v++) {
        if (dist[1][v] == INF) continue;
        ans = max(ans, dist[1][v]);
    }
    cout << ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    dijkstra0();

    buildH();

    pathp();

    dijkstra1();

    output();
}