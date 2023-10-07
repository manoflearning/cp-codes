// 가격이 더 싸거나 같은 농장에 방문하면, 더 이상 다익스트라를 진행할 필요가 없다.
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 303030;
const ll INF = 1e18;

int N, M, K, T;
struct Edge { ll w; int v; };
vector<Edge> adj[MAXN];

vector<int> en;
int isEn[MAXN];

vector<pll> st;
int cost[MAXN];

void input() {
    cin >> N >> M >> K >> T;
    en.resize(K);
    for (auto& i : en) { cin >> i; isEn[i] = 1; }
    st.resize(T);
    for (auto& i : st) {
        cin >> i.fr >> i.sc;
        cost[i.fr] = i.sc;
    }
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

struct State {
    ll w; int v;
    bool operator<(const State& rhs) const {
        return w > rhs.w;
    }
};
ll ans[MAXN];

void dijkstra(int v, ll c) {
    unordered_map<int, ll> dist;

    priority_queue<State> pq;
    dist[v] = 0;
    ans[v] = min(ans[v], c);
    pq.push({ dist[v], v });

    if (isEn[v]) return;

    ll upper = INF;
    
    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (upper < w) continue;
        ans[v] = min(ans[v], c);
        if (upper == w) continue;
        if (isEn[v]) continue;
        
        for (auto& i : adj[v]) {
            // if (0 < cost[i.v] && cost[i.v] <= c) continue;
            if (!dist.count(i.v) || w + i.w < dist[i.v] ) {
                dist[i.v] = w + i.w;
                if (isEn[i.v]) upper = min(upper, dist[i.v]);
                pq.push({ dist[i.v], i.v });
            }
        }
    }
}

void solve() {
    for (int i = 0; i < MAXN; i++) ans[i] = INF;

    for (auto& i : st) {
        dijkstra(i.fr, i.sc);
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

    solve();

    for (auto& i : en) {
        cout << (ans[i] == INF ? -1 : ans[i]) << ' ';
    }
}