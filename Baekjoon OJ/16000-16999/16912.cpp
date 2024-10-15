#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const int MAXM = 101010;

int flag;
struct Seg {
    vector<vector<pii>> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int l, int r, pii val, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            t[n].push_back(val);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
    }
}seg;

struct UF {
    vector<int> par, siz, stk;
    void build(int n) {
        par.resize(n + 1);
        iota(all(par), 0);
        siz.resize(n + 1, 1);
    }
    int find(int x) {
        if (par[x] == x) return x;
        return find(par[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (siz[u] < siz[v]) swap(u, v);
        siz[u] += siz[v]; par[v] = u;
        stk.push_back(v);
    }
    void restore() {
        int v = stk.back();
        stk.pop_back();
        siz[par[v]] -= siz[v]; par[v] = v;
    }
}uf;

int n, m;
pii a[MAXM];
int ans[MAXM];
map<pii, int> mp;

void input() {
    cin >> n >> m;
    seg.build(m);
    uf.build(n);
    for (int i = 1; i <= m; i++) {
        int op, u, v;
        cin >> op >> u >> v;
        if (u > v) swap(u, v);
        if (op == 1) mp[{ u, v }] = i;
        if (op == 2) seg.modify(mp[{ u, v }], i, { u, v }), mp.erase({ u, v });
        if (op == 3) a[i] = { u, v };
    }
    for (auto& it : mp)
        seg.modify(it.sc, m, it.fr);
}

void odc(int n = 1, int nl = 1, int nr = flag) {
    int cnt = 0;
    for (auto it : seg.t[n]) {
        uf.merge(it.fr, it.sc); cnt++;
    }
    if (nl == nr) {
        if (nl <= m && a[nl].fr) {
            ans[nl] = (uf.find(a[nl].fr) == uf.find(a[nl].sc));
        }
        while (cnt--) uf.restore();
        return;
    }
    int mid = (nl + nr) >> 1;
    odc(n << 1, nl, mid);
    odc(n << 1 | 1, mid + 1, nr);
    while (cnt--) uf.restore();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    odc();

    for (int i = 1; i <= m; i++)
        if (a[i].fr) cout << ans[i] << '\n';
}
