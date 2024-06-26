//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const ll INF = 1e18;

struct Edge { 
    int v; ll w; int l, num; 
    bool operator==(const Edge& rhs) const { return l == rhs.l; }
    bool operator<(const Edge& rhs) const {
        if (l ^ rhs.l) return l < rhs.l;
        else return w < rhs.w;
    }
};
int n, m;
vector<Edge> adj[101010];
ll lu[101010];
vector<int> edgeV(101010, -1);
vector<pii> idxOfEdge(101010, { -1, -1 });

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; ll w; int l;
        cin >> u >> v >> w >> l;
        adj[u].push_back({ v, w, l, i + 1 });
        adj[v].push_back({ u, w, l, i + 1 });
        lu[i + 1] = l;
    }
}

map<ll, int> L[101010], R[101010];

void sorting() {
    // sorting
    for (int v = 1; v <= n; v++) {
        sort(adj[v].begin(), adj[v].end(), [&](const Edge& lhs, const Edge& rhs) {
            return lhs.l < rhs.l;
        });
    }
    for (int v = 1; v <= n; v++) {
        for (int i = 0; i < sz(adj[v]); i++) {
            auto& it = adj[v][i];
            if (edgeV[it.num] == -1) edgeV[it.num] = v, idxOfEdge[it.num].fr = i;
            else idxOfEdge[it.num].sc = i;
            if (!L[v].count(it.l)) L[v][it.l] = i;
            R[v][it.l] = i;
        }
    }
}

struct state { ll w; int num, pv, pidx; };
vector<state> dist1[101010], dist2[101010];

struct Node {
    ll w; int v, num;
    bool operator<(const Node& rhs) const { return w > rhs.w; }
};

void dijkstra1() {
    // dijkstra
    for (int v = 1; v <= n; v++) 
        dist1[v].resize(sz(adj[v]), { INF, -1, -1, -1 });

    priority_queue<Node> pq;
    pq.push({ 0, 1, 0 });
    dist1[1][0] = { 0, 0, -1, -1 };

    while (sz(pq)) {
        auto [w, v, num] = pq.top();
        pq.pop();

        int st = -1;
        if (num == 0) st = 0;
        else st = (edgeV[num] == v ? idxOfEdge[num].fr : idxOfEdge[num].sc);
        
        if (dist1[v][st].w < w) continue;

        for (int i = L[v][lu[num]]; i < sz(adj[v]); i++) {
            auto& it = adj[v][i];
            if (it.l < lu[num]) continue;
            int nst = (edgeV[it.num] == v ? idxOfEdge[it.num].sc : idxOfEdge[it.num].fr);
            if (dist1[it.v][nst].w <= w + it.w) continue;
            pq.push({ w + it.w, it.v, it.num });
            dist1[it.v][nst] = { w + it.w, it.num, v, st };
        }
    }
}

void dijkstra2() {
    // dijkstra
    for (int v = 1; v <= n; v++) 
        dist2[v].resize(sz(adj[v]), { INF, -1, -1, -1 });

    priority_queue<Node> pq;
    pq.push({ 0, 1, 101009 });
    dist2[1][sz(adj[1]) - 1] = { 0, 101009, -1, -1 };

    while (sz(pq)) {
        auto [w, v, num] = pq.top();
        pq.pop();

        int st = -1;
        if (num == 101009) st = sz(adj[1]) - 1;
        else st = (edgeV[num] == v ? idxOfEdge[num].fr : idxOfEdge[num].sc);
        
        if (dist2[v][st].w < w) continue;

        for (int i = R[v][lu[num]]; i >= 0; i--) {
            auto& it = adj[v][i];
            if (lu[num] < it.l) continue;
            int nst = (edgeV[it.num] == v ? idxOfEdge[it.num].sc : idxOfEdge[it.num].fr);
            if (dist2[it.v][nst].w <= w + it.w) continue;
            pq.push({ w + it.w, it.v, it.num });
            dist2[it.v][nst] = { w + it.w, it.num, v, st };
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

    input();
    
    sorting();

    dijkstra1();
    lu[101009] = INF;
    R[1][lu[101009]] = sz(adj[1]) - 1;
    dijkstra2();

    ll ans = INF, mn = 0, j = 0, idx1 = 0, idx2 = 0;
    for (int i = 0; i < sz(adj[2]); i++) {
        while (j < sz(adj[2]) && adj[2][j].l <= adj[2][i].l) {
            if (dist1[2][j].w < dist1[2][mn].w) mn = j;
            j++;
        }
        if (dist1[2][mn].w + dist2[2][i].w < ans) {
            ans = dist1[2][mn].w + dist2[2][i].w;
            idx1 = mn, idx2 = i;
        }
    }
    //for (auto& i : dist2[1]) cout << i.w << ' ';
    cout << ans << '\n';
    stack<int> stk;
    int v = 2;
    while (dist1[v][idx1].num != 0) {
        stk.push(dist1[v][idx1].num);
        int tmpv = dist1[v][idx1].pv, tmpidx = dist1[v][idx1].pidx;
        v = tmpv, idx1 = tmpidx;
    }

    while (sz(stk)) { cout << stk.top() << ' '; stk.pop(); }
    v = 2;
    while (dist2[v][idx2].num != 101009) {
        cout << dist2[v][idx2].num << ' ';
        int tmpv = dist2[v][idx2].pv, tmpidx = dist2[v][idx2].pidx;
        v = tmpv, idx2 = tmpidx;
    }
}