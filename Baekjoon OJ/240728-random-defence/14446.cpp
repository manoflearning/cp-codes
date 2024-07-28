#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 101010;
const int R = 347;

int n, a[N], par[N];
vector<int> t[N];
int in[N], out[N], p;
int b[N];

struct Query {
    int s, e, idx;
    bool operator<(const Query& rhs) const {
        if (s / R != rhs.s / R) return s / R < rhs.s / R;
        else return e < rhs.e;
    }
};
vector<Query> qu;
int ans[N];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) {
        cin >> par[i];
        t[par[i]].push_back(i);
    }
}

void cc() {
    vector<int> c(1, -1);
    for (int i = 1; i <= n; i++) {
        c.push_back(a[i]);
    }
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(all(c), a[i]) - c.begin();
    }
}

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll val) {
        p += flag - 1;
        for (t[p] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

void dfs(int v) {
    in[v] = ++p;
    b[in[v]] = a[v];
    for (auto& i : t[v]) dfs(i);
    out[v] = p;
    // cout << v << ' ' << in[v] << ' ' << out[v] << '\n';
    qu.push_back({ in[v], out[v], v });
}

void add(int idx) {
    seg.add(b[idx], 1);
}
void del(int idx) {
    seg.add(b[idx], -1);
}

void mo() {
    seg.build(n);
    int s = qu[0].s, e = qu[0].e;
    for (int i = s; i <= e; i++) add(i);
    ans[qu[0].idx] = seg.query(b[s] + 1, n);
    for (int i = 1; i < sz(qu); i++) {
        while (qu[i].s < s) add(--s);
        while (e < qu[i].e) add(++e);
        while (s < qu[i].s) del(s++);
        while (qu[i].e < e) del(e--);
        ans[qu[i].idx] = seg.query(b[s] + 1, n);
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

    cc();

    dfs(1);

    sort(all(qu));

    mo();

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}