#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size() 

struct PST {
    int flag;
    struct Node { int l, r, val; };
    vector<Node> t;
    vector<int> root;
    vector<int> vertexHash;
    
    void addNode() { t.push_back({ -1, -1, 0 }); };
    void build(int l, int r, int n) {
        assert(0 <= n && n < sz(t));
        if (l == r) { t[n].val = 0; return; }
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        int mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
        t[n].val = t[t[n].l].val + t[t[n].r].val;
    }
    void build(int Flag, int v) {
        addNode();
        root.push_back(sz(t) - 1);
        flag = Flag;
        build(1, flag, root[0]);
    }
} pst;

int n, a[101010];
vector<int> adj[101010], cc;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void coordinateCompress() {
    cc.push_back(-1);
    for (int i = 1; i <= n; i++) 
        cc.push_back(a[i]);
    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(cc.begin(), cc.end(), a[i]) - cc.begin();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    coordinateCompress();
}