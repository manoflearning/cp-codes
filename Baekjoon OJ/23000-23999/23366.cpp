#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXN = 101010;
const ll INF = 1e18;

int n, m;
int st, en;
ll tot, dist[MAXN];
struct Edge { int p, v; };
vector<Edge> adj[MAXN];

void input() {
    cin >> n >> m;
    cin >> st >> en >> tot;
    for (int i = 0; i < m; i++) {
        int u, v, p;
        cin >> u >> v >> p;
        adj[u].push_back({ p, v });
        adj[v].push_back({ p, u });
    }
}

void solve() {
    for (int i = 0; i < MAXN; i++) dist[i] = INF;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[st] = 0;
    pq.push({ dist[st], st });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (dist[v] < w) continue;

        ll candies_cnt = tot - w;

        for (auto& i : adj[v]) {
            ll nw = w + (candies_cnt * i.p + 99) / 100;
            if (dist[i.v] <= nw) continue;
            dist[i.v] = nw;
            pq.push({ dist[i.v], i.v });
        }
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

    solve();
    
    cout << tot - dist[en];
}