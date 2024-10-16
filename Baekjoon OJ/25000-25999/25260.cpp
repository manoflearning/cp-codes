#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int MAXD = 16;

int flag;
struct Seg {
    vector<pair<int, int>> t;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1, { INF, INF });
    }
    void modify(int p, pair<int, int> val) {
        p += flag - 1;
        t[p] = min(t[p], val);
        for (; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    pair<int, int> query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return { INF, INF };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

int n, q;
pair<int, int> a[101010];
int par[101010][MAXD + 1];

void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i].first >> a[i].second;
}

void cc() {
    vector<int> c(1, 0);
    for (int i = 1; i <= n; i++) {
        c.push_back(a[i].first);
        c.push_back(a[i].second);
    }
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    for (int i = 1; i <= n; i++) {
        a[i].first = lower_bound(c.begin(), c.end(), a[i].first) - c.begin();
        a[i].second = lower_bound(c.begin(), c.end(), a[i].second) - c.begin();
    }
}

void formTree() {
    seg.build(202020);
    for (int i = 1; i <= n; i++) {
        seg.modify(a[i].second, { a[i].first, i });
    }
    
    for (int i = 1; i <= n; i++) {
        pair<int, int> res = seg.query(a[i].first, a[i].second);
        par[i][0] = res.second;
    }
}

void buildSparseTable() {
    for (int x = 1; x <= MAXD; x++) {
        for (int i = 1; i <= n; i++) {
            par[i][x] = par[par[i][x - 1]][x - 1];
        }
    }
}

int isCross(int st, int en) { return (a[st].first <= a[en].second && a[en].second <= a[st].second); }
int needToGo(int st, int en) { return a[en].second < a[st].first; }

int lca(int st, int en) {
    if (st == en) return 0;
    if (isCross(st, en)) return 1;
    int ret = 0;
    for (int x = MAXD; x >= 0; x--) {
        if (needToGo(par[st][x], en)) {
            st = par[st][x];
            ret += (1 << x);
        }
    }
    if (isCross(par[st][0], en)) return ret + 2;
    return INF;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    input();

    cc();

    formTree();

    buildSparseTable();

    while (q--) {
        int st, en;
        cin >> st >> en;
        swap(st, en);

        int res = lca(st, en);
        if (res == INF) cout << "impossible\n";
        else cout << res << '\n';
    }
}