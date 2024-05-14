// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct UF {
    vector<int> uf;
    void init(int N) {
        uf.clear();
        uf.resize(N + 1, -1);
    }
    int find(int v) {
        if (uf[v] < 0) return v;
        return uf[v] = find(uf[v]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
}uf;

int flag;
struct Seg {
    vector<int> t;
    void init(int N) {
        t.clear();
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int v) {
        for (t[v += flag - 1]++; v > 1; v >>= 1)
            t[v >> 1] = (t[v] * t[v ^ 1]) % MOD;
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 1;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) * query(l, r, n << 1 | 1, mid + 1, nr) % MOD;
    }
}seg;

int N, H, X[202020];

int chunk[202020];
vector<int> lm(202020, INF), rm(202020, -INF);
int ladj[202020], radj[202020];
ll ans[202020];

void input() {
    cin >> N >> H;
    for (int i = 1; i <= N; i++) cin >> X[i];
}

void get_chunk() {
    vector<int> ord(N);
    iota(all(ord), 1);
    sort(all(ord), [](int p1, int p2) {
        return X[p1] < X[p2];
    });

    uf.init(N);
    for (int i = 0; i + 1 < sz(ord); i++) {
        int u = ord[i], v = ord[i + 1];
        if (X[u] + H > X[v]) uf.merge(u, v);
    }

    vector<int> c(1, -INF);
    for (int i = 1; i <= N; i++) c.push_back(uf.find(i));

    sort(all(c));
    c.erase(unique(all(c)), c.end());

    vector<int> chunk_prv(sz(c), INF);
    for (auto& i : ord) {
        chunk[i] = lower_bound(all(c), uf.find(i)) - c.begin();
        lm[chunk[i]] = min(lm[chunk[i]], X[i]);
        rm[chunk[i]] = max(rm[chunk[i]], X[i]);
        
        int prv = chunk_prv[chunk[i]];
        ladj[i] = prv;
        if (prv != INF) radj[chunk_prv[chunk[i]]] = i;
        chunk_prv[chunk[i]] = i;
    }
}

// if it ends in time i:
// (1) chunk including i: 
// (2) chunk excluding i:

void solve() {
    seg.init(N);
    vector<int> ord(N);

    for (int i = 1; i <= N; i++) {
        int ch_idx = chunk[i];

        ll res1 = seg.query(1, ch_idx - 1) * seg.query(1, ch_idx + 1) % MOD;
        ll res2 = 0;

        if (X[i] == lm[ch_idx]) { seg.add(ch_idx); res2++; }
        if (X[i] == rm[ch_idx] && lm[ch_idx] != rm[ch_idx]) { seg.add(ch_idx); res2++; }
        
        if (ladj[ch_idx] < i) { seg.add(ch_idx); res2++; }
        if (radj[ch_idx] < i) { seg.add(ch_idx); res2++; }

        ans[i] = res1 * res2 % MOD;
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

    get_chunk();

    solve();

    for (int i = 1; i <= N; i++)
        cout << ans[i] << ' ';
}