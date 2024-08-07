#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

const int INF = 1e9 + 7;

struct Edge { int u, v, idx; };
struct vidx { int v, idx; };

int n, st, en = -1;
set<int> node;
unordered_map<int, vector<vidx>> adj;
unordered_map<int, int> ind, outd;
vector<Edge> edge[2];
multimap<pii, int> edgeIdx;

void input() {
    cin >> n >> st;
    for (int i = 0; i < n; i++) {
        int u, v, bit;
        cin >> u >> v >> bit;
        edge[bit].push_back({ u, v, i + 1 });
        if (bit) {
            node.insert(u); node.insert(v);
            edgeIdx.insert({ { u, v }, i + 1 });
        }
    }
}

void buildGraph() {
    for (auto& i : edge[1]) {
        outd[i.u]++, ind[i.v]++;
        adj[i.u].push_back({ i.v, i.idx });
    }
}

int doesEulerPathExist() {
    // euler circuit
    int cnt = 0;
    for (auto v : node) {
        cnt += (ind[v] != outd[v]);
    }
    if (!cnt) return 1;

    // euler path
    if (ind[st] + 1 != outd[st]) return 0;
    for (auto v : node) {
        if (v == st) continue;
        if (ind[v] == outd[v]) continue;
        if (ind[v] == outd[v] + 1) {
            if (en == -1) en = v;
            else return 0;
            continue;
        }
        return 0;
    }
    return 1;
}

unordered_map<int, int> nxt;
int edgeVi[101010];
vector<int> res;

void dfs(int v) {
    for (auto& i = nxt[v]; i < sz(adj[v]); i++) {
        auto it = adj[v][i];
        while (i < sz(adj[v]) && !edgeVi[it.idx]) {
            edgeVi[it.idx] = 1;
            dfs(it.v);
        }
    }
    res.push_back(v);
}

vector<int> ans;
void constructAnswer() {
    for (auto& i : edge[0]) {
        if (i.u != st) ans.push_back(i.idx);
    }

    int bit = 1;
    reverse(res.begin(), res.end());
    for (int i = 0; i + 1 < sz(res); i++) {
        int u = res[i], v = res[i + 1];
        auto it = edgeIdx.find({ u, v });
        ans.push_back(it->sc);
        edgeIdx.erase(it);

        if (bit && v != st) {
            for (auto& j : edge[0]) {
                if (j.u == st) ans.push_back(j.idx);
            }
            bit = 0;
        }
    }
}

int validAnswer() {
    set<int> s;
    for (auto& i : ans) {
        if (s.count(i)) return 0;
        s.insert(i);
    }
    return sz(s) == n;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildGraph();

    if (!doesEulerPathExist()) {
        cout << "No"; return 0;
    }

    dfs(st);
    
    constructAnswer();

    if (!validAnswer()) {
        cout << "No"; return 0;
    }

    cout << "Yes\n";
    for (auto& i : ans)
        cout << i << ' ';
}