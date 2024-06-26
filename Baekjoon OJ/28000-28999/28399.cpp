#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int MAXN = 202020;
const ll INF = 1e18;

int N, M, K;
struct wv { ll w; int v; };
vector<wv> adj[MAXN];
int vtop[MAXN], isEnd[MAXN], isStart[MAXN];
int nxt[MAXN];

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
	memset(vtop, -1, sizeof(vtop));
	for (int i = 0; i < K; i++) {
		int len; cin >> len;
		int prv = -1;
		for (int j = 0; j < len; j++) {
			int x; cin >> x;
			vtop[x] = i;
			if (j == 0) isStart[x] = 1;
			if (j == len - 1) isEnd[x] = 1;
			
			if (prv != -1) nxt[prv] = x;
			prv = x;
		}
	}
}

struct State {
	ll w; bool onP; int v;
	bool operator<(const State& rhs) const {
		return w > rhs.w;
	}
};
ll dist[MAXN][2];

void dijkstra() {
	// initialize
	for (int i = 0; i < MAXN; i++) {
		dist[i][0] = dist[i][1] = INF;
	}

	// base case
	priority_queue<State> pq;
	bool stOnP = isStart[1];
	dist[1][stOnP] = 0;
	pq.push({ dist[1][stOnP], stOnP, 1 });

	// inductive step
	while (!pq.empty()) {
		auto [w, onP, v] = pq.top();
		pq.pop();

		if (dist[v][onP] < w) continue;

		for (auto& i : adj[v]) {
			ll nw = w + i.w;
			bool nOnP = (onP && nxt[v] == i.v) || isStart[i.v];
			if (vtop[i.v] == -1) assert(!nOnP);
			int u = i.v;
			if (nOnP && isEnd[u]) continue;
			if (dist[u][nOnP] > nw) {
				dist[u][nOnP] = nw;
				pq.push({ dist[u][nOnP], nOnP, u });
			}
		}
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	dijkstra();

	for (int v = 1; v <= N; v++) {
		ll ans = min(dist[v][0], dist[v][1]);
		// cout << v << ' ' << dist[v][0] << ' ' << dist[v][1] << '\n';
		cout << (ans == INF ? -1 : ans) << ' ';
	}
}