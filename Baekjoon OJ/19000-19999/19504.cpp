#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define fr first
#define sc second

const ll INF = 1e18;

struct Edge {
    int v; ll w; int l, num;
    bool operator<(const Edge& rhs) const { return l < rhs.l; }
    bool operator<=(const Edge& rhs) const { return l <= rhs.l; }
};

int n, m;
vector<vector<Edge>> adj;

void input() {
    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; int l;
        cin >> u >> v >> w >> l;
        adj[u].push_back({ v, w, l, i + 1 });
        adj[v].push_back({ u, w, l, i + 1 });
    }
}

struct Node {
    int v; ll w; int l;
    bool operator<(const Node& rhs) const {
        return w > rhs.w;
    }
};

struct prvNode {
    int num, v, idx;
    prvNode(int Num, int V, int Idx) { num = Num; v = V; idx = Idx; }
    bool operator!=(const prvNode& rhs) const {
        return num != rhs.num || v != rhs.v || idx != rhs.idx;
    }
};

vector<ll> increase, decrease;
vector<vector<prvNode>> prvin, prvde;

void dijkstra1() {
    vector<vector<ll>> dist(n + 1);
    prvin.resize(n + 1);
    for (int v = 1; v <= n; v++) {
        dist[v].resize(sz(adj[v]), INF);
        prvin[v].resize(sz(adj[v]), { -1, -1, -1 });
    }

    priority_queue<Node> pq;
    pq.push({ 1, 0, 0 });
    dist[1][0] = 0;
    prvin[1][0] = { 0, 0, 0 };
    
    while (sz(pq)) {
        auto [v, w, l] = pq.top();
        pq.pop();

        Edge du; du.l = l;
        int st = lower_bound(all(adj[v]), du) - adj[v].begin();

        for (int idx = st; idx < sz(adj[v]); idx++) {
            auto it = adj[v][idx];

            int nidx = lower_bound(all(adj[it.v]), it) - adj[it.v].begin();
            if (w + it.w < dist[it.v][nidx]) {
                pq.push({ it.v, w + it.w, it.l });
                dist[it.v][nidx] = w + it.w;
                prvin[it.v][nidx] = { it.num, v, st };
            }
        }
    }

    increase = dist[2];
}

void dijkstra2() {
    vector<vector<ll>> dist(n + 1);
    prvde.resize(n + 1);
    for (int v = 1; v <= n; v++) {
        dist[v].resize(sz(adj[v]), INF);
        prvde[v].resize(sz(adj[v]), { -1, -1, -1 });
    }

    priority_queue<Node> pq;
    pq.push({ 1, 0, adj[1].back().l });
    dist[1][sz(adj[1]) - 1] = 0;
    prvde[1][sz(adj[1]) - 1] = { 0, 0, 0 };
    
    while (sz(pq)) {
        auto [v, w, l] = pq.top();
        pq.pop();

        Edge du; du.l = l;
        int st = upper_bound(all(adj[v]), du) - adj[v].begin() - 1;

        for (int idx = st; idx >= 0; idx--) {
            auto it = adj[v][idx];

            int nidx = upper_bound(all(adj[it.v]), it) - adj[it.v].begin() - 1;
            if (w + it.w < dist[it.v][nidx]) {
                pq.push({ it.v, w + it.w, it.l });
                dist[it.v][nidx] = w + it.w;
                prvde[it.v][nidx] = { it.num, v, st };
            }
        }
    }

    decrease = dist[2];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int v = 1; v <= n; v++) {
        sort(all(adj[v]));
    }

    dijkstra1();
    dijkstra2();

    ll ans = INF;
    ll mn = INF; int mnidx = -1;
    int v1 = -1, v2 = -1, idx1 = -1, idx2 = -1;
    for (int i = 0; i < sz(increase); i++) {
        if (increase[i] < mn) {
            mn = increase[i];
            mnidx = i;
        }
        if (mn + decrease[i] < ans) {
            ans = mn + decrease[i];
            v1 = v2 = 2;
            idx1 = mnidx, idx2 = i;
        }
    }

    cout << ans << '\n';
    stack<int> print1;
    for (; prvin[v1][idx1] != prvNode(0, 0, 0); ) {
        print1.push(prvin[v1][idx1].num);

        prvNode tmp = prvin[v1][idx1];
        v1 = tmp.v;
        mnidx = tmp.idx;
    }
    while (sz(print1)) {
        cout << print1.top() << ' ';
        print1.pop();
    }
    for (; prvde[v2][idx2] != prvNode(0, 0, 0); ) {
        cout << prvde[v2][idx2].num << ' ';

        prvNode tmp = prvde[v2][idx2];
        v2 = tmp.v;
        idx2 = tmp.idx;
    }
}