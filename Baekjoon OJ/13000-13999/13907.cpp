//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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

int n, m, k;
int st, en;
struct wv { ll w; int v; };
vector<wv> adj[1010];

ll dist[1010][1010];

struct Node {
    int v, cnt; ll w;
    bool operator<(const Node& rhs) const {
        return w > rhs.w;
    }
};

void dijkstra() {
    for (int i = 0; i < 1010; i++) {
        for (int j = 0; j < 1010; j++) dist[i][j] = INF;
    }

    priority_queue<Node> pq;
    pq.push({ st, 0, 0 });
    dist[st][0] = 0;

    while (sz(pq)) {
        auto [v, cnt, w] = pq.top();
        pq.pop();

        if (dist[v][cnt] < w) continue;
        if (cnt == n - 1) continue;
        
        for (auto& i : adj[v]) {
            if (w + i.w < dist[i.v][cnt + 1]) {
                pq.push({ i.v, cnt + 1, w + i.w });
                dist[i.v][cnt + 1] = w + i.w;
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

	cin >> n >> m >> k;
    cin >> st >> en;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }

    dijkstra();

    ll all = 0;
    for (int i = 0; i <= k; i++) {
        ll ans = 1e18;
        for (int j = 0; j <= n; j++) {
            ans = min(ans, dist[en][j] + j * all);
        }
        cout << ans << '\n';

        ll x; cin >> x;
        all += x;
    }

	return 0;
}