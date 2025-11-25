#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 101010;
constexpr int D = 18;
constexpr int Q = 101010;

int n, q;
int par[N][D], ro = -1;
vector<int> chd[N];

vector<pii> qu[Q];
ll ans[Q];

int flag;
struct Seg {
    vector<int> t;
    void build() {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int kth(int k, int n = 1, int nl = 1, int nr = flag) {
        if (nl == nr) return nl;
        int mid = (nl + nr) >> 1;
        if (k <= t[n << 1]) return kth(k, n << 1, nl, mid);
        else return kth(k - t[n << 1], n << 1 | 1, mid + 1, nr);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg;

int sum[N], dep[N];
int in[N], out[N], idx;

struct MergeSortTree {
    static constexpr int MAX_MST = 1 << 17;
    vector<int> t[MAX_MST << 1];
    void build() {
        for (int i = 1; i <= n; i++) {
            t[in[i] + MAX_MST].push_back(i);
        }
        for (int i = MAX_MST - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }
    int query(int l, int r, int k, int n = 1, int nl = 0, int nr = MAX_MST - 1) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r)
            return upper_bound(all(t[n]), k) - t[n].begin();
        int mid = (nl + nr) >> 1;
        return query(l, r, k, n << 1, nl, mid) + query(l, r, k, n << 1 | 1, mid + 1, nr);
    }
} mst;

void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> par[i][0];
        if (par[i][0]) {
            chd[par[i][0]].push_back(i);
        } else {
            ro = i;
        }
    }
    for (int i = 1; i <= q; i++) {
        ll k; cin >> k;

        int x = (k - 1) / n + 1;
        qu[x].push_back({(k - 1) % n, i});
    }
}

void build_sparse_table() {
    for (int d = 1; d < D; d++) {
        for (int i = 1; i <= n; i++) {
            par[i][d] = par[par[i][d - 1]][d - 1];
        }
    }
}

void dfs(int v) {
    in[v] = ++idx;
    sum[v] = 1;
    for (auto &i : chd[v]) {
        dep[i] = dep[v] + 1;
        dfs(i);
        sum[v] += sum[i];
    }
    out[v] = idx;
}

// int get_lca_naive(int st, int &rem) {
//     vector<pii> ord;
//     for (int v = st, prv = 0; v != 0; prv = v, v = par[v][0]) {
//         ord.push_back({v, sum[v] - sum[prv]});
//     }
//     sort(all(ord));
//     for (const auto &[v, cnt] : ord) {
//         if (rem < cnt) return v;
//         rem -= cnt;
//     }
//     return -1;
// }
int get_lca(int &rem) {
    int lc = seg.kth(rem + 1);
    rem -= seg.query(1, lc - 1);
    return lc;
}

int get_anc(int st, int len) {
    for (int d = 0; d < D; d++) {
        if (len & (1 << d))
            st = par[st][d];
    }
    return st;
}

int get_y(int x, int lc, int rem) {
    int z = -1;
    if (x == lc) {
        z = 0;
    } else {
        z = get_anc(x, dep[x] - dep[lc] - 1);
    }
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        int res = mst.query(in[lc], out[lc], mid) - mst.query(in[z], out[z], mid);
        if (res > rem) r = mid;
        else l = mid + 1;
    }
    return l;
}

void dfs2(int x) {
    if (par[x][0]) {
        seg.modify(par[x][0], sum[par[x][0]] - sum[x]);
    }
    seg.modify(x, sum[x]);

    for (auto &[rem, idx] : qu[x]) {
        int lc = get_lca(rem);
        int y = get_y(x, lc, rem);

        ll res = 0;
        res += (ll)n * n * (x - 1);
        res += (ll)n * (lc - 1);
        res += y - 1;

        // cout << "x = " << x << " | lca(x, y) = " << lc << " | y = " << y << '\n';

        ans[idx] = res;
    }

    seg.modify(x, 0);

    for (auto &i : chd[x]) dfs2(i);

    if (par[x][0])
        seg.modify(par[x][0], 0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    build_sparse_table();

    dfs(ro);

    seg.build();
    mst.build();

    dfs2(ro);

    for (int i = 1; i <= q; i++)
        cout << ans[i] << '\n';
}
