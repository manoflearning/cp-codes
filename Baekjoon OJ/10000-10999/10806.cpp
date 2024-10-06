#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 101010;

struct UF {
    vector<int> uf;
    void build() {
        uf.clear();
        uf.resize(MAXN, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] = V;
    }
}uf;

int n, m;
vector<int> adj[MAXN], t[MAXN];
map<pii, int> mp;
set<pii> aEdge;
set<pii> tEdge;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        mp[{ min(u, v), max(u, v) }]++;
    }
}

int dfsn[MAXN], dCnt;

int dfs(int now, int prv) {
    int ret = dfsn[now] = ++dCnt;

    int childCnt = 0;
    for (int next : adj[now]) {
        if (next == prv) continue;

        if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
        else {
            childCnt++;
            int tmp = dfs(next, now);
            ret = min(ret, tmp);

            if (tmp > dfsn[now] && mp[{ min(now, next), max(now, next) }] == 1) {
                aEdge.insert({ min(now, next), max(now, next) });
            }
        }
    }
    return ret;
}

void getBCC() {
    memset(dfsn, -1, sizeof(dfsn));
    for (int v = 1; v <= n; v++)
        if (dfsn[v] == -1) dfs(v, -1);
}

void build_tree() {
    uf.build();

    for (int v = 1; v <= n; v++) {
        for (auto& u : adj[v]) {
            if (!aEdge.count({ min(u, v), max(u, v) }))
                uf.merge(u, v);
        }
    }

    for (auto& i : aEdge) {
        int u = uf.find(i.fr);
        int v = uf.find(i.sc);
        assert(u != v);
        t[u].push_back(v);
        t[v].push_back(u);
        tEdge.insert({ min(u, v), max(u, v) });
    }
}

vector<int> leaves;
void get_leaves(int v, int prv) {
    if (sz(t[v]) == 1) {
        leaves.push_back(v);
        return;
    }

    vector<int> arr;
    for (auto& i : t[v]) {
        if (i != prv) get_leaves(i, v);
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

    getBCC();

    build_tree();

    if (sz(tEdge) == 0) {
        cout << 0 << '\n';
        exit(0);
    }
    if (sz(tEdge) == 1) {
        auto [u, v] = *tEdge.begin();
        cout << 1 << '\n';
        cout << u << ' ' << v << '\n';
        exit(0);
    }

    int rt = -1;
    for (int v = 1; v <= n; v++) {
        if (sz(t[v]) >= 2) {
            rt = v;
            break;
        }
        assert(v < n);
    }

    get_leaves(rt, -1);

    vector<pii> ans;
    for (int i = 0; i + sz(leaves) / 2 < sz(leaves); i++) {
        int j = i + sz(leaves) / 2;

        int u = leaves[i], v = leaves[j];
        ans.push_back({ u, v });
    }

    cout << sz(ans) << '\n';
    for (auto& [u, v] : ans)
        cout << u << ' ' << v << '\n';
}
