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
const ll INF = 1e18 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Edge {
    ll w; int v, b;
};

struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};

ll n, m, s, e, dist[5050];
vt<Edge> adj[5050], adj2[5050], adj3[5050];

void init() {
    for (int i = 0; i < 5050; i++) dist[i] = INF;
}

void input() {
    cin >> n >> m >> s >> e;
    for (int i = 0; i < m; i++) {
        int u, v, w, b1, b2;
        cin >> u >> v >> w >> b1 >> b2;
        adj[u].push_back({ 2 * w, v, b1 });
        adj[v].push_back({ 2 * w, u, b2 });
    }
    s <<= 1, e <<= 1;
}

void dijkstra1() {
    priority_queue<wv> pq;
    dist[1] = 0;
    pq.push({ 0, 1 });

    while (sz(pq)) {
        int v = pq.top().v; ll w = pq.top().w;
        pq.pop();

        if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            ll nw = w + i.w;
            if (nw > s) continue;
            if (dist[i.v] <= nw) continue;
            dist[i.v] = nw;
            pq.push({ nw, i.v });
        }
    }
}

void buildadj2() {
    for (int v = 1; v <= n; v++) {
        if (dist[v] > s) continue;
        for (auto& i : adj[v]) {
            if (dist[v] + i.w <= s) continue;
            i.w -= s - dist[v];
        }
    }
}

void dijkstra2() {
    priority_queue<wv> pq;
    
    for (int v = 1; v <= n; v++) {
        if (dist[v] != INF) pq.push({ dist[v], v });
    }

    while (sz(pq)) {
        int v = pq.top().v; ll w = pq.top().w;
        pq.pop();

        if (dist[v] < w) continue;
        if (w < s) w = s;
        
        for (auto& i : adj[v]) {
            ll nw = w + (i.b + 1) * i.w;

            if (nw > e) continue;
            if (dist[i.v] <= nw) continue;
            
            dist[i.v] = nw;
            pq.push({ nw, i.v });
        }
    }
}

void buildadj3() {
    for (int v = 1; v <= n; v++) {
        if (dist[v] > e) continue;
        for (auto& i : adj[v]) {
            if (dist[v] + (i.b + 1) * i.w <= e) continue;
            
            if (i.b) i.w -= (e - max(s, dist[v])) / 2;
            else i.w -= e - max(s, dist[v]);
        }
    }
}

void dijkstra3() {
    priority_queue<wv> pq;
    
    for (int v = 1; v <= n; v++) {
        if (dist[v] != INF) pq.push({ dist[v], v });
    }

    while (sz(pq)) {
        int v = pq.top().v; ll w = pq.top().w;
        pq.pop();

        if (dist[v] < w) continue;
        if (w < e) w = e;
        
        for (auto& i : adj[v]) {
            ll nw = w + i.w;
            if (dist[i.v] <= nw) continue;
            
            dist[i.v] = nw;
            pq.push({ nw, i.v });
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

    init();

    input();

    dijkstra1();

    buildadj2();
    dijkstra2();

    buildadj3();
    dijkstra3();

    ll ans = 0;
    for (int v = 1; v <= n; v++) {
        ans = max(ans, dist[v]);
    }

    cout << ans / 2;
    if (ans & 1) cout << ".5";

    return 0;
}