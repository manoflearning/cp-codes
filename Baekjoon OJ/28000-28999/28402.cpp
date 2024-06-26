#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 252525;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

const int sq = 549;
struct Query {
    int s, e, v;
    bool operator<(const Query& rhs) const {
        if (s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
        return (s / sq) & 1 ? e < rhs.e : e > rhs.e;
    }
};
vector<Query> qu;

int n, a[MAXN];
vector<int> t1[MAXN], t2[MAXN];
int in1[MAXN], out1[MAXN], in2[MAXN], out2[MAXN];
int rin1[MAXN];
int ans[MAXN];

void input() {
    cin >> n;
    for (int v = 1; v <= n; v++) cin >> a[v];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t1[u].push_back(v);
        t1[v].push_back(u);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t2[u].push_back(v);
        t2[v].push_back(u);
    }
}

int cnt = 0;
void dfs1(int v, int prv) {
    in1[v] = ++cnt;
    rin1[cnt] = v;
    for (auto& i : t1[v]) if (i != prv) dfs1(i, v);
    out1[v] = cnt;
}
void dfs2(int v, int prv) {
    in2[v] = ++cnt;
    for (auto& i : t2[v]) if (i != prv) dfs2(i, v);
    out2[v] = cnt;
}

void add(int v) { seg.modify(in2[v], a[v]); }
void del(int v) { seg.modify(in2[v], 0); }
int query(int v) { return seg.query(in2[v], out2[v]); }

void f() {
    for (int v = 1; v <= n; v++) {
        qu.push_back({ in1[v], out1[v], v });
    }
    sort(all(qu));

    seg.build(n);
    
    int s = qu[0].s, e = qu[0].e;
    for (int i = s; i <= e; i++) add(rin1[i]);
    ans[qu[0].v] = query(qu[0].v);
    
    for (int i = 1; i < sz(qu); i++) {
        auto& it = qu[i];
        while (it.s < s) add(rin1[--s]);
        while (e < it.e) add(rin1[++e]);
        while (s < it.s) del(rin1[s++]);
        while (it.e < e) del(rin1[e--]);
        ans[it.v] = query(it.v);
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

    dfs1(1, -1);
    cnt = 0;
    dfs2(1, -1);

    f();

    for (int v = 1; v <= n; v++) {
        assert(ans[v] > 0);
        cout << ans[v] << '\n';
    }
}