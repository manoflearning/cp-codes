#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 5050;
const int INF = 1e9;

int n, m;
struct Edge { int w, v; };
vector<Edge> g[MAXN], rg[MAXN];
int dist[MAXN][MAXN], rdist[MAXN][MAXN];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w1, w2;
        cin >> u >> v >> w1 >> w2;
        g[u].push_back({ w1, v });
        g[v].push_back({ w2, u });
        rg[u].push_back({ w2, v });
        rg[v].push_back({ w1, u });
    }
}

struct State {
    int w, v;
    bool operator<(const State& rhs) const {
        return w > rhs.w;
    }
};
void dijkstra(int st) {
    priority_queue<State> pq;
    dist[st][st] = 0;
    pq.push({ dist[st][st], st });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (dist[st][v] < w) continue;

        for (auto& i : g[v]) {
            if (i.v == 1) continue;
            if (w + i.w < dist[st][i.v]) {
                dist[st][i.v] = w + i.w;
                pq.push({ dist[st][i.v], i.v });
            }
        }
    }
}
void rdijkstra(int st) {
    priority_queue<State> pq;
    rdist[st][st] = 0;
    pq.push({ rdist[st][st], st });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (rdist[st][v] < w) continue;

        for (auto& i : rg[v]) {
            if (i.v == 1) continue;
            if (w + i.w < rdist[st][i.v]) {
                rdist[st][i.v] = w + i.w;
                pq.push({ rdist[st][i.v], i.v });
            }
        }
    }
}

void getDist() { // O(nm log(n))
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            dist[i][j] = rdist[i][j] = INF;
        }
    }
    
    dijkstra(1);
    rdijkstra(1);
    for (auto& i : g[1]) {
        dijkstra(i.v);
        rdijkstra(i.v);
    }
}

int ans = INF;

void threeEdgePath() {
    for (auto& i : g[1]) {
        for (auto& j : g[i.v]) {
            if (j.v != 1) ans = min(ans, i.w + j.w + rdist[1][j.v]);
        }
    }
}

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, INF);
    }
    void modify(int p, int val) {
        t[p + flag - 1] = min(t[p + flag - 1], val);
        for (p += flag - 1; p > 1; p >>= 1) {
            t[p >> 1] = min(t[p], t[p ^ 1]);
        }
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

void solve() {
    for (int v = 2; v <= n; v++) {
        if (sz(g[v]) == 1) continue;

        seg.build(n);

        vector<pair<int, pii>> arr;
        for (auto& i : g[1]) if (i.v != v)
            for (auto& j : rg[v]) if (j.v != 1)
                arr.push_back({ i.w + dist[i.v][j.v] + j.w, { min(i.v, j.v), max(i.v, j.v) }});
        for (auto& i : rg[1]) if (i.v != v)
            for (auto& j : g[v]) if (j.v != 1) {
                seg.modify(i.v, i.w + rdist[i.v][j.v] + j.w);
                seg.modify(j.v, i.w + rdist[i.v][j.v] + j.w);
            }

        for (auto& i : arr) {
            int res = INF;
            res = min(res, seg.query(1, i.sc.fr - 1));
            res = min(res, seg.query(i.sc.fr + 1, i.sc.sc - 1));
            res = min(res, seg.query(i.sc.sc + 1, n));
            ans = min(ans, res + i.fr);
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
    
    getDist();

    threeEdgePath();

    solve();

    cout << ans;
}