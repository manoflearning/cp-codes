#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 262626;

int n;
ll a[MAXN], sum[MAXN], prdc[MAXN];
int flag;

int in[MAXN], out[MAXN];
ll ans[MAXN];

int p;
void dfs(int v) {
    in[v] = ++p;

    sum[v] = a[v];
    if (v < flag) {
        dfs(v << 1);
        dfs(v << 1 | 1);

        sum[v] += sum[v << 1];
        sum[v] += sum[v << 1 | 1];
        prdc[v] += prdc[v << 1];
        prdc[v] += prdc[v << 1 | 1];
    } else prdc[v] = 1;

    out[v] = p;
}

struct Fenwick { // 1-indexed
  int flag;
  vector<__int128_t> t;
  void build(int N) {
    flag = N;
    t.resize(flag + 1);
  }
  void add(int l, int r, __int128_t val) { // add a val to all elements in interval [l, r]
    for (; l <= flag; l += l & -l) t[l] += val;
    for (r++; r <= flag; r += r & -r) t[r] -= val;
  }
  __int128_t query(int x) {
    __int128_t ret = 0;
    for (; x; x ^= x & -x) ret += t[x];
    return ret;
  }
} fw_n, fw_d;

struct Node {
    __int128_t n, d; int v;
    bool operator<(const Node &o) const {
        return n * o.d > o.n * d;
    }
};
priority_queue<Node> pq;

bool vis[MAXN];
void solve() {
    assert(p == n);

    fw_n.build(n);
    fw_d.build(n);
    for (int i = flag; i <= n; i++) {
        fw_n.add(in[i], in[i], sum[i]);
        fw_d.add(in[i], in[i], prdc[i]);
        pq.push({fw_n.query(in[i]), fw_d.query(in[i]), i});
    }
    for (int i = flag - 1; i >= 1; i--) {
        fw_n.add(in[i], in[i], a[i]);
    }

    while (!pq.empty()) {
        auto [n, d, v] = pq.top();
        pq.pop();

        if (n != fw_n.query(in[v]) || d != fw_d.query(in[v])) {
            pq.push({fw_n.query(in[v]), fw_d.query(in[v]), v});
            continue;
        }

        vis[v] = 1;
        ans[v] = (n + d - 1) / d;

        if (v > 1) {
            fw_n.add(in[v >> 1], out[v >> 1], sum[v]);
            fw_d.add(in[v >> 1], out[v >> 1], prdc[v]);
            fw_n.add(in[v], out[v], -sum[v]);
            fw_d.add(in[v], out[v], -prdc[v]);

            if (vis[v] && vis[v ^ 1]) {
                pq.push({fw_n.query(in[v >> 1]), fw_d.query(in[v >> 1]), v >> 1});
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    flag = (n + 1) / 2;

    dfs(1);

    solve();

    for (int i = 1; i <= n; i++) {
        assert(vis[i]);
        cout << ans[i] << ' ';
    }
}
