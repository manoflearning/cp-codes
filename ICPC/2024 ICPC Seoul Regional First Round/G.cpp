#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

map<pii, int> mp;
struct UF {
    vector<int> uf;
    void build(int n) {
        uf.resize(n + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[V] = U;
    }
} uf;

struct Edge {
    int u, v, idx;
};

int n, m;
vector<Edge> e[101010];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[w].push_back({u, v, i});
        // adj[u].push_back({i, w, v});
        // adj[v].push_back({i, w, u});
    }
}

vector<int> cc;
vector<Edge> vs;
set<int> aEdge;

int ans[101010];
struct Edge2 { int idx, w, v; };
vector<vector<Edge2>> adj;

int dCnt;
vector<int> dfsn(101010, -1);

void each_init() {
    mp.clear();
    cc.clear();
    vs.clear();
    adj.clear();
    dfsn.clear();
    aEdge.clear();
    dCnt = 0;
    dfsn.clear();
}

int dfs(int now, int prv) {
    int ret = dfsn[now] = ++dCnt;
    int childCnt = 0;
    for (auto [idx, _, next] : adj[now]) {
        if (next == prv) continue;
        if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
        else {
            childCnt++;
            int tmp = dfs(next, now);
            ret = min(ret, tmp);
            if (tmp > dfsn[now]/* && mp[{min(next, now), max(next, now)}] == 1*/) aEdge.insert(idx);
        }
    }
    return ret;
}

void coor_comp() {
    cc.push_back(-1);
    for (auto &i : vs) {
        cc.push_back(i.u);
        cc.push_back(i.v);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (auto &i : vs) {
        i.u = lower_bound(all(cc), i.u) - cc.begin();
        i.v = lower_bound(all(cc), i.v) - cc.begin();
    }
    adj.resize(sz(cc));
    dfsn.resize(sz(cc), -1);
}

void solve() {
    for (int w = 1; w <= 100'000; w++) {
        if (e[w].empty()) continue;

        each_init();

        for (auto &[u, v, idx] : e[w]) {
            if (uf.find(u) == uf.find(v)) {
                ans[idx] = 3;
                continue;
            }
            else {
                int U = uf.find(u), V = uf.find(v);
                if (U > V) swap(U, V);
                vs.push_back({U, V, idx});
            }
        }

        coor_comp();
        
        for (auto &[u, v, idx] : vs) {
            if (u > v) swap(u, v);
            mp[{u, v}]++;
            adj[u].push_back({idx, -1, v});
            adj[v].push_back({idx, -1, u});
        }

        for (int v = 1; v < sz(cc); v++) {
            if (dfsn[v] == -1) dfs(v, -1);
        }

        for (auto &[u, v, idx] : vs) {
            if (ans[idx] == 3) continue;
            // cout << idx << ' ' << mp[{u, v}] << '\n';
            if (mp[{u, v}] == 1 && aEdge.count(idx)) ans[idx] = 1;
            else ans[idx] = 2;
        }
        // for (auto& i : aEdge) cout << i << '\n';

        for (auto &[u, v, idx] : e[w]) uf.merge(u, v);
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    input();    

    uf.build(n + 1);

    solve();

    // for (int w = 1; w <= 100000; w++)
    // for (auto& [u, v, _] : e[w]) {
    //     cout << uf.find(u) << ' ' << uf.find(v) << '\n';
    // }

    for (int v = 1; v <= m; v++)
        cout << ans[v] << '\n';
}
