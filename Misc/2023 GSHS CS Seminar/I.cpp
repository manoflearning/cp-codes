// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXN = 303030;
const ll INF = 1e18;

int N, M, K, T;
vector<int> a;
vector<pii> b;
vector<pii> adj[MAXN];

void input() {
    cin >> N >> M >> K >> T;
    a.resize(K);
    for (auto& i : a) cin >> i;
    b.resize(T);
    for (auto& i : b) cin >> i.fr >> i.sc;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

ll dist[MAXN];

void dijkstra() {
    for (int i = 0; i < MAXN; i++) dist[i] = INF;

    priority_queue<pll> pq;
    for (auto& i : a) {
        dist[i] = 0;
        pq.push({ -0, i });
    }

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        w *= -1;

        if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            if (w + i.fr < dist[i.sc]) {
                dist[i.sc] = w + i.fr;
                pq.push({ -dist[i.sc], i.sc });
            }
        }
    }
}

vector<int> dag[MAXN];
int ind[MAXN];

void buildDAG() {
    for (int v = 1; v <= N; v++) {
        if (dist[v] == INF) continue;
        for (auto& i : adj[v]) {
            if (dist[i.sc] + i.fr == dist[v]) {
                dag[v].push_back(i.sc);
                ind[i.sc]++;
            }
        }
    }
}

vector<ll> ans(MAXN, INF);

void solve() {
    for (auto& i : b) ans[i.fr] = i.sc;

    queue<int> q;
    for (int v = 1; v <= N; v++) {
        if (!ind[v]) q.push(v);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& i : dag[v]) {
            ans[i] = min(ans[i], ans[v]);
            ind[i]--;
            if (!ind[i]) q.push(i);
        }
    }

    for (auto& i : a) {
        cout << (ans[i] == INF ? -1 : ans[i]) << ' ';
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

    buildDAG();
    
    solve();
}