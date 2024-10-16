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

const int MAXN = 202020, MAXT = 202020;

int n, t;
// unordered_map<int, vector<int>> mp[MAXT];
struct Edge { int v, ti; };
vector<Edge> adj[MAXN];

int k, a[MAXT];
vector<ll> eachT[MAXT];

void input() {
    cin >> n >> t;
    for (int i = 1; i <= t; i++) {
        int m; cin >> m;
        while (m--) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back({ v, i });
            adj[v].push_back({ u, i });
        }
    }
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
        eachT[a[i]].push_back(i);
    }
    for (int i = 1; i <= t; i++) eachT[i].push_back(INF);
}

ll dist[MAXN];
struct State {
    ll w; int v;
    bool operator<(const State& rhs) const {
        return w > rhs.w;
    }
};
priority_queue<State> pq;

void dijkstra() {
    for (int i = 0; i < MAXN; i++) dist[i] = INF;
    
    dist[1] = 1;
    pq.push({ dist[1], 1 });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        
        if (dist[v] < w) continue;

        int ti = a[dist[v]];
        
        for (auto& i : adj[v]) {
            ll nw = *lower_bound(all(eachT[i.ti]), dist[v]) + 1;
            if (dist[i.v] <= nw) continue;
            dist[i.v] = nw;
            pq.push({ dist[i.v], i.v });
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dijkstra();

    // for (int v = 1; v <= n; v++) {
    //     cout << v << ' ' << dist[v] << '\n';
    // }

    cout << (dist[n] == INF ? -1 : dist[n] - 1);
}