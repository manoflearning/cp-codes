#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 252525;
const int MAXD = 18;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
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

int n, a[MAXN];
vector<int> ra[MAXN];
vector<int> adj[MAXN], chd[MAXN];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ra[a[i]].push_back(i);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int in[MAXN], out[MAXN], p;
ll rin[MAXN];

void dfs(int v, int prv) {
    in[v] = ++p;
    rin[in[v]] = v;
    for (auto& i : adj[v]) {
        if (i != prv) {
            dfs(i, v);
            chd[v].push_back(i);
        }
    }
    out[v] = p;
}

ll psum[MAXN];
ll ans1 = 0, ans2 = 0, ans3 = 0;

void solve() {
    seg.build(p);

    for (int co = 1; co <= n; co++) {
        if (sz(ra[co]) <= 1) continue;

        for (auto& v : ra[co]) seg.modify(in[v], 1);

        for (auto& v : ra[co]) {
            psum[in[v]]++;
            psum[in[v] + 1]--;

            if (seg.query(1, in[v] - 1) + seg.query(out[v] + 1, p) > 0) {
                psum[in[v] + 1]++;
                psum[out[v] + 1]--;
            }

            for (auto& u : chd[v]) {
                if (seg.query(in[u], out[u])) {
                    psum[1]++;
                    psum[in[u]]--;
                    psum[out[u] + 1]++;
                    psum[p + 1]--;
                }
            }
        }

        for (auto& v : ra[co]) seg.modify(in[v], 0);
    }

    for (int i = 1; i <= p; i++) {
        psum[i] += psum[i - 1];
        if (psum[i] > 0) continue;
        ans1 += 1;
        ans2 += rin[i];
        ans3 += rin[i] * rin[i];
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

    dfs(1, 0);

    solve();

    cout << ans1 << '\n' << ans2 << '\n' << ans3 << '\n';
}
