#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int flag;  // array size
struct Seg {  // 1-indexed
    vector<ll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    // add a value to all elements in interval [l, r]
    void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            assert(lazy[n] == 0);
            lazy[n] = value;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, value, n << 1, nl, mid);
        modify(l, r, value, n << 1 | 1, mid + 1, nr);
        t[n] = max(t[n << 1], t[n << 1 | 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
        propagate(n);
        if (r < nl || nr < l) return -INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n) {
        if (lazy[n] != 0) {
            if (n < flag) {
                lazy[n << 1] += lazy[n];
                lazy[n << 1 | 1] += lazy[n];
            }
            t[n] += lazy[n];
            lazy[n] = 0;
        }
    }
}seg;

int n, deg[202020], vi[202020], dep[202020];
vector<int> adj[202020];
vector<int> arr(1, -1);

void dfs(int v) {
    vi[v] = 1;
    arr.push_back(v);
    for (auto& i : adj[v]) 
        if (!vi[i]) dfs(i);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }

    queue<pii> q;
    for (int v = 1; v <= n; v++)
        if (deg[v] == 1) q.push({ v, -1 });

    while (!q.empty()) {
        auto [v, prv] = q.front();
        q.pop();
        vi[v] = 1;
        for (auto& i : adj[v]) {
            if (i == prv) continue;
            deg[i]--, dep[i] = dep[v] + 1;
            if (deg[i] == 1) q.push({ i, v });
        }
    }

    ll ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) 
        if (!vi[i]) ans1++;

    for (int v = 1; v <= n; v++)
        if (!vi[v]) { dfs(v); break; }

    seg.build(sz(arr) - 1);
    for (int i = 1; i < sz(arr); i++) {
        int v = arr[i];
        seg.modify(i, i, dep[v] + i - 1);
    }

    assert(sz(arr) > 3);

    for (int i = 1; i < sz(arr); i++) {
        int v = arr[i];
        ll res = dep[v] + max(seg.query(1, i - 1), seg.query(i + 1, sz(arr) - 1));
        ans2 = max(ans2, res);
        seg.modify(1, sz(arr) - 1, -1);

        ll val = seg.query(i, i);
        seg.modify(i, i, -val);
        //assert(seg.query(i, i) == 0);
        //assert(seg.t[flag + i - 1] == 0);
        seg.modify(i, i, dep[v] + sz(arr) - 2);
        //assert(seg.query(i, i) == dep[v] + sz(arr) - 2);
        //assert(seg.t[flag + i - 1] == dep[v] + sz(arr) - 2);
    }

    cout << ans1 << ' ' << ans2;
}