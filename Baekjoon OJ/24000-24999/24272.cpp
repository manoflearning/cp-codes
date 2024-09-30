#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

const int MAXN = 101010;

int flag;
struct Seg {
    vector<int> t, cnt;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        cnt.resize(flag << 1);
    }
    void modify(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return;

        if (l <= nl && nr <= r) t[n] += val;
        else {
            int mid = (nl + nr) >> 1;
            modify(l, r, val, n << 1, nl, mid);
            modify(l, r, val, n << 1 | 1, mid + 1, nr);
        }

        if (t[n] > 0) {
            cnt[n] = (nr - nl + 1);
        } else if (nl < nr) {
            cnt[n] = cnt[n << 1] + cnt[n << 1 | 1];
        } else cnt[n] = 0;
    }
    int query() { return cnt[1]; }
}seg;

int n;
struct Edge {
    int u, v, dir; // 0: --, 1: ->, 2: <-
};
map<pii, int> e;
vector<int> t[MAXN];

int in[MAXN], out[MAXN], p;

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        string s;
        cin >> u >> s >> v;

        int dir = -1;
        if (s == "--") dir = 0;
        else if (s == "->") dir = 1;
        else if (s == "<-") dir = 2;

        if (u > v) {
            swap(u, v);
            if (dir) dir ^= 1;
        }

        e[{ u, v }] = dir;
        
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    in[v] = ++p;
    for (auto& i : t[v]) {
        if (i != prv) dfs(i, v);
    }
    out[v] = p;
}

bool is_par(int chd, int par) {
    return in[par] < in[chd];
}

void modify(int u, int v, int val, int dir) {
    if (dir == 0) return;

    if (!is_par(u, v)) {
        swap(u, v);
        dir = (dir & 1 ? dir + 1 : dir - 1);
    }

    if (dir == 1) {
        seg.modify(1, in[u] - 1, val);
        seg.modify(out[u] + 1, n, val);
    }
    if (dir == 2) {
        seg.modify(in[u], out[u], val);
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

    dfs(1, -1);

    seg.build(n);
    for (auto it : e) {
        auto [u, v] = it.first;
        auto dir = it.second;
        modify(u, v, 1, dir);
    }

    int q; cin >> q;
    while (q--) {
        int u, v;
        string s;
        cin >> u >> s >> v;

        int dir = -1;
        if (s == "--") dir = 0;
        else if (s == "->") dir = 1;
        else if (s == "<-") dir = 2;

        if (u > v) {
            swap(u, v);
            if (dir) dir = (dir & 1 ? dir + 1 : dir - 1);
        }

        modify(u, v, -1, e[{ u, v }]);
        e[{ u, v }] = dir;
        modify(u, v, 1, e[{ u, v }]);

        cout << n - seg.query() << '\n';
    }
}
