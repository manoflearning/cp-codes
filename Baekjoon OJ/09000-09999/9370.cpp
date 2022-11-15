#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;
const int MAX = 2020;

struct wv {
	ll w; int bit, v;
	bool operator<(const wv& rhs) const {
		return w > rhs.w;
	}
};

int n, m, t;
int s, g, h;
vector<int> a;
vector<wv> adj[MAX];
ll dist1[MAX][4], dist2[MAX];

void init() {
    a.clear();
    for (int i = 0; i < MAX; i++) {
        adj[i].clear();
        dist1[i][0] = dist1[i][1] = dist1[i][2] = dist1[i][3] = INF;
        dist2[i] = INF;
    }
}

void input() {
	cin >> n >> m >> t;
    cin >> s >> g >> h;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, 0, v });
        adj[v].push_back({ w, 0, u });
	}
    a.resize(t);
    for (auto& i : a) cin >> i;
}

void dijkstra1() {
	priority_queue<wv> pq;
    int sb = 0;
    if (s == g) sb |= 1;
    if (s == h) sb |= 2;
	pq.push({ 0, sb, s });
	dist1[s][sb] = 0;

	while (!pq.empty()) {
		int v = pq.top().v, b = pq.top().bit;
		ll w = pq.top().w;
		pq.pop();
        
		if (w > dist1[v][b]) continue;
		for (auto& i : adj[v]) {
            int nb = b;
            if (i.v == g) nb |= 1;
            if (i.v == h) nb |= 2;

			if (dist1[i.v][nb] > w + i.w) {
				dist1[i.v][nb] = w + i.w;
				pq.push({ w + i.w, nb, i.v });
			}
		}
	}
}

void dijkstra2() {
	priority_queue<wv> pq;
	pq.push({ 0, 0, s });
	dist2[s] = 0;

	while (!pq.empty()) {
		int v = pq.top().v;
		ll w = pq.top().w;
		pq.pop();
        //cout << v << ' ' << w << '\n';
		if (w > dist2[v]) continue;
		for (auto& i : adj[v]) {
			if (dist2[i.v] > w + i.w) {
				dist2[i.v] = w + i.w;
				pq.push({ w + i.w, 0, i.v });
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

	int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        dijkstra1();

        dijkstra2();

        vector<int> ans;
        for (auto& i : a) {
            if (dist1[i][3] != INF && dist1[i][3] == dist2[i]) 
                ans.push_back(i);
        }
        
        sort(ans.begin(), ans.end());

        for (auto& i : ans)
            cout << i << ' ';
        cout << '\n';
    }

	return 0;
}