#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};

int n, m, st, en, k;
vector<vector<wv>> adj(101010);
vector<int> a;

void dijkstra(int v0, vector<ll>& dist) {
    priority_queue<wv> pq;
    pq.push({ 0, v0 });
    dist[v0] = 0;
    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        if (dist[v] < w) continue;
        for (auto& i : adj[v]) {
            if (w + i.w < dist[i.v]) {
                pq.push({ w + i.w, i.v });
                dist[i.v] = w + i.w;
            }
        }
    }
}

ll w[20][20], started[20], ended[20];
ll dp[20][1 << 20];

ll f(int v, int bit) {
    ll& ret = dp[v][bit];
    if (ret != -1) return ret;
    if (bit == (1 << sz(a)) - 1) return ret = ended[v];

    ret = INF;
    for (int i = 0; i < a.size(); i++) {
        if (bit & (1 << i)) continue;
        ret = min(ret, w[v][i] + f(i, bit | (1 << i)));
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    cin >> st >> en >> k;
    a.resize(k);
    for (auto& i : a) cin >> i;

    for (int i = 0; i < a.size(); i++) {
        vector<ll> dist(101010, INF);
        dijkstra(a[i], dist);
        for (int j = 0; j < a.size(); j++) {
            if (i == j) continue;
            w[i][j] = dist[a[j]];
        }
        started[i] = dist[st];
        ended[i] = dist[en];
    }

    for (int i = 0; i < 20; i++)
        memset(dp[i], -1, sizeof(dp[i]));

    ll ans = INF;
    for (int i = 0; i < a.size(); i++)
        ans = min(ans, started[i] + f(i, 1 << i));
    cout << (ans == INF ? -1 : ans);
}