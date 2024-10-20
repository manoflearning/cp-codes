#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

struct wv { ll w, v; };
struct wvcnt {
    ll w, v, cnt;
    bool operator<(const wvcnt& rhs) const {
        if (cnt ^ rhs.cnt) return cnt > rhs.cnt;
        return w > rhs.w; 
    }
};

int n, st = 0, en;
int b[1010];
vector<wv> adj[1010];
int dist[1010][1010];

void dijkstra() {
    for (int i = 0; i < 1010; i++) {
        for (int j = 0; j < 1010; j++) {
            dist[i][j] = INF;
        }
    }

    priority_queue<wvcnt> pq;
    pq.push({ 0, st, 0 });
    dist[st][0] = 0;

    while (!pq.empty()) {
        auto [w, v, cnt] = pq.top();
        pq.pop();

        if (dist[v][cnt] < w) continue;
        if (v == en) {
            cout << cnt << ' ' << w;
            return;
        }

        for (auto& i : adj[v]) {
            int nw = w + i.w;
            int nv = i.v;
            int ncnt = cnt + (b[v] != b[i.v]);
            if (dist[nv][ncnt] > nw) {
                dist[nv][ncnt] = nw;
                pq.push({ nw, nv, ncnt });
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

    cin >> n >> en;
    for (int i = 0; i < n; i++) cin >> b[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            if (!x) continue;
            adj[i].push_back({ x, j });
        }
    }

    dijkstra();
}