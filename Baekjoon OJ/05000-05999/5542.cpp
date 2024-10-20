#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const ll INF = 1e18;

struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};

struct Query {
    int u, v;
    ll l, r;
};

int n, m, k, q;
vector<wv> adj[101010];
vector<int> st;
vector<Query> query;

void input() {
    cin >> n >> m >> k >> q;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    st.resize(k);
    for (auto& i : st) cin >> i;
    query.resize(q);
    for (auto& i : query) {
        cin >> i.u >> i.v;
        i.l = 0, i.r = 200'000 * 1'000;
    }
}

ll dist[101010];

void dijkstra() {
    for (int i = 0; i < 101010; i++) dist[i] = INF;

    priority_queue<wv> pq;
    for (auto& i : st) {
        pq.push({ 0, i });
        dist[i] = 0;
    }

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        //if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            if (w + i.w < dist[i.v]) {
                pq.push({ w + i.w, i.v });
                dist[i.v] = w + i.w;
            }
        }
    }
}

// union find
vector<int> uf(101010, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] = V;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dijkstra();

    // solve
    vector<wv> arr;
    for (int v = 1; v <= n; v++) {
        arr.push_back({ dist[v], v });
        //cout << dist[v] << ' ' << v << '\n';
    }
    sort(arr.begin(), arr.end());

    for (int k = 0; k < 32; k++) {
        // initialize
        uf.clear();
        uf.resize(101010, -1);

        map<ll, vector<int>> pbs;
        for (int i = 0; i < q; i++) {
            if (query[i].l == query[i].r) continue;
            ll mid = (query[i].l + query[i].r + 1) >> 1;
            pbs[-mid].push_back(i);
        }

        //
        int pv = 0;
        for (auto& i : pbs) {
            ll mid = -i.fr;
            while (pv < n && arr[pv].w >= mid) {
                int v = arr[pv].v;
                for (auto& e : adj[v]) {
                    if (dist[e.v] >= mid) merge(e.v, v);
                }
                pv++;
            }

            for (auto& j : i.sc) {
                if (find(query[j].u) == find(query[j].v)) query[j].l = mid;
                else query[j].r = mid - 1;
            }
        }
    }

    for (auto& i : query)
        cout << i.l << '\n';
}