#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define ll long long

const ll INF = 1e18;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<pair<ll, string>> t;
	void build(int n) {
        t.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, { INF, "" });
		// for (int i = flag; i < flag + n; i++) cin >> t[i];
		// for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, pair<ll, string> val) {  // set value at position p
		for (t[p += flag - 1] = val; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	pair<ll, string> query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return { INF, "" };
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int n, m, h, Q, k;
vector<string> a;
struct Node { int id; char type; };
vector<Node> b;
struct Edge { int u, v; ll w; };
vector<Edge> c;

vector<char> id_to_type;
vector<vector<pair<ll, int>>> adj;

void input() {
    cin >> n >> m >> h >> Q;
    a.resize(n);
    for (auto& i : a) cin >> i;
    b.resize(m);
    for (auto& i : b) cin >> i.id >> i.type;
    m = 303;
    cin >> k;
    c.resize(k);
    for (auto& i : c) cin >> i.u >> i.v >> i.w;
}

// vector<int> cc(1, -1);
// inline int get_idx(int x) { return lower_bound(all(cc), x) - cc.begin(); }
void coordinate_compression() {
    // for (auto& i : b) {
    //     cc.push_back(i.id);
    // }
    // sort(all(cc));
    // cc.erase(unique(all(cc)), cc.end());
    id_to_type.resize(m);
    for (auto& i : b) {
        // i.id = lower_bound(all(cc), i.id) - cc.begin();
        id_to_type[i.id] = i.type;
    }
    adj.resize(m);
    for (auto& i : c) {
        // i.u = lower_bound(all(cc), i.u) - cc.begin();
        // i.v = lower_bound(all(cc), i.v) - cc.begin();
        adj[i.u].push_back({ i.w, i.v });
        adj[i.v].push_back({ i.w, i.u });
    }
}

vector<int> source_B, source_C;
vector<ll> dist_B, dist_C;

void dijkstra(const vector<int>& sources, vector<ll>& dist) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    for (auto& v : sources) {
        dist[v] = 0;
        pq.push({ dist[v], v });
    }

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            if (dist[i.second] <= i.first + w) continue;
            dist[i.second] = i.first + w;
            pq.push({ dist[i.second], i.second });
        }
    }
}

vector<int> id_to_cache_node;
void get_cache_node(const vector<int>& sources) {
    id_to_cache_node.resize(m + 1, 1e9);

    for (auto& i : sources) id_to_cache_node[i] = i;

    vector<int> ord(m);
    iota(all(ord), 1);
    sort(all(ord), [&](int p1, int p2) {
        return dist_C[p1] < dist_C[p2];
    });

    for (auto& v : ord) {
        for (auto& i : adj[v]) {
            if (dist_C[i.second] != i.first + dist_C[v]) continue;
            id_to_cache_node[i.second] = min(id_to_cache_node[i.second], id_to_cache_node[v]);
        }
    }
}

vector<set<string>> vis;

map<string, int> id_and_s_to_time[303];

void solve() {
    for (int v = 1; v <= m; v++) {
        if (id_to_type[v] == 'B') source_B.push_back(v);
        if (id_to_type[v] == 'C') source_C.push_back(v);
    }

    dist_B.resize(m + 1, INF);
    dist_C.resize(m + 1, INF);

    dijkstra(source_B, dist_B);
    dijkstra(source_C, dist_C);

    get_cache_node(source_C);

    vis.resize(m + 1);

    seg.build(Q + 5);

    for (int ti = 1; ti <= Q; ti++) {
        int v; string s;
        cin >> v >> s;

        assert(id_to_type[v] == 'R');

        ll ans = dist_C[v];

        int cn = id_to_cache_node[v];

        if (!vis[cn].count(s)) {
            while (sz(vis[cn]) >= h) {
                auto [last_ti, t] = seg.query(1, Q);
                vis[cn].erase(t);
                id_and_s_to_time[cn].erase(t);
                seg.modify(last_ti, { INF, "" });
            }

            vis[cn].insert(s);
            id_and_s_to_time[cn][s] = ti;
            seg.modify(ti, { ti, s });

            ans += dist_B[cn];
        } else {
            int last_ti = id_and_s_to_time[cn][s];
            id_and_s_to_time[cn][s] = ti;
            seg.modify(last_ti, { INF, "" });
            seg.modify(ti, { ti, s });
        }

        cout << 2 * ans << '\n';
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

    coordinate_compression();

    solve();
}