#include <bits/stdc++.h>
using namespace std;

int flag;
struct Seg {
    vector<int> t;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1]; 
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n, q;
int a[101010], sum[101010];
vector<int> t[101010];

struct Query {
    int idx, l, r;
    bool operator<(const Query& rhs) const { return l < rhs.l; }
};
vector<Query> query;
vector<int> ans;

void input() {
    cin >> n >> q;
    for (int v = 1; v <= n; v++) cin >> a[v];
    for (int v = 2; v <= n; v++) {
        int u; cin >> u;
        t[u].push_back(v);
    }
    query.resize(q);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        auto& it = query[i];
        cin >> it.l >> it.r;
        it.idx = i;
    }
}

void dfs(int v) {
    sum[v] = a[v];
    for (auto& i : t[v]) {
        dfs(i);
        sum[v] += sum[i];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(query.begin(), query.end());
    
    dfs(1);
    
    seg.build(n);
    seg.modify(1, sum[1]);

    int lb = 1;
    for (auto& i : query) {
        while (lb < i.l) {
            for (auto& i : t[lb]) 
                seg.modify(i, sum[i]);
            lb++;
        }

        ans[i.idx] = seg.query(i.l, i.r);
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}