#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;
const ll MAX = 30303;

struct wv {
    ll w; int v, pidx;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};

inline ll Hash(ll x, ll y, ll z) {
    return MAX * MAX * x + MAX * y + z;
}

int n, m, k;
int st, en, ind[MAX];
vector<wv> adj[MAX];
vector<ll> radj[MAX], dist[MAX];
unordered_set<ll> s;

void input() {
    cin >> m >> n >> k;
    cin >> st >> en;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        radj[v].push_back(u);
        ind[v]++;
    }

    adj[n].push_back({ 0, st });
    radj[st].push_back(n);
    ind[st]++;

    for (int i = 0; i < k; i++) {
        ll x, y, z;
        cin >> x >> y >> z;
        s.insert(Hash(x, y, z));
    }
}

ll dijkstra() {
    priority_queue<wv> pq;
    pq.push({ 0, st, ind[st] - 1 });
    dist[st][ind[st] - 1] = 0;

    while (sz(pq)) {
        int v = pq.top().v, prv = radj[v][pq.top().pidx], pidx = pq.top().pidx;
        ll w = pq.top().w;
        pq.pop();

        if (v == en) return w;
        if (dist[v][pidx] < w) continue;

        for (auto& i : adj[v]) {
            if (s.find(Hash(prv, v, i.v)) != s.end()) continue;
            int npidx = lower_bound(radj[i.v].begin(), radj[i.v].end(), v) - radj[i.v].begin();
            if (dist[i.v][npidx] <= w + i.w) continue;
            pq.push({ w + i.w, i.v, npidx });
            dist[i.v][npidx] = w + i.w;
        }
    }

    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    for (int i = 0; i < n; i++) {
        dist[i].resize(ind[i], INF);
        sort(radj[i].begin(), radj[i].end());
    }

    cout << dijkstra();

	return 0;
}