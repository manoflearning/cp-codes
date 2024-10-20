#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long dondble
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct wv { 
    ll w; int v; 
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};

int n, m, st, en, c, dist[11];
vt<wv> adj[11];

int dijkstra(int mx) {
    for (int i = 0; i < 11; i++) dist[i] = INF;

    priority_queue<wv> pq;
    pq.push({ 0, st });
    dist[st] = 0;

    while (sz(pq)) {
        int v = pq.top().v, w = pq.top().w;
        pq.pop();

        if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            if (i.w > mx) continue;
            if (dist[i.v] <= w + i.w) continue;
            dist[i.v] = w + i.w;
            pq.push({ w + i.w, i.v });
        }
    }

    return dist[en];
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> st >> en >> c;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }

    int l = 1, r = 1000;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (dijkstra(mid) <= c) r = mid;
        else l = mid + 1;
    }

    if (dijkstra(l) > c) {
        cout << -1;
        return 0;
    }

    cout << l;

    return 0;
}