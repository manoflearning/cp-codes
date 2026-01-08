#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

// what: maintain prefix sums with point updates and range sum queries.
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n]; a[0] unused; kth needs all values >= 0.
// usage: fenwick fw; fw.build(a); fw.add(p, x); fw.sum(l, r); fw.kth(k);
struct fenwick {
    int n;
    vector<ll> a, t;
    void init(int n_) {
        // goal: allocate arrays for size n.
        n = n_;
        a.assign(n + 1, 0);
        t.assign(n + 1, 0);
    }
    void add(int p, ll val) {
        // goal: a[p] += val.
        a[p] += val;
        for (int i = p; i <= n; i += i & -i) t[i] += val;
    }
    ll sum(int x) const {
        // result: prefix sum on [1..x].
        ll ret = 0;
        for (int i = x; i > 0; i -= i & -i) ret += t[i];
        return ret;
    }
    ll sum(int l, int r) const { return sum(r) - sum(l - 1); }
};

int n;
vector<vector<int>> t, rdep;
vector<int> dep, cnt, cnt_w_chd, p, in, out;
int idx;

void init() {
    idx = 0;
}

void input() {
    cin >> n;
    t.assign(n + 1, vector<int>());
    rdep.assign(n + 1, vector<int>());
    dep.assign(n + 1, 0);
    cnt.assign(n + 1, 0);
    cnt_w_chd.assign(n + 1, 0);
    p.assign(n + 1, 0);
    in.assign(n + 1, 0);
    out.assign(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    dep[v] = dep[prv] + 1;
    rdep[dep[v]].push_back(v);
    cnt[dep[v]]++;
    p[v] = prv;
    if (v == 1 || sz(t[v]) > 1) cnt_w_chd[dep[v]]++;
    for (auto &i : t[v]) {
        if (i != prv) dfs(i, v);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        dfs(1, 0);

        int ans = cnt[2] + 1;
        for (int i = 2; i <= n; i++) {
            ans = max(ans, cnt[i] + (cnt_w_chd[i - 1] == 1));
        }
        cout << ans << '\n';

        vector<vector<int>> ops(ans);
        vector<int> loc(n + 1, -1);

        for (int d = 1; d <= n; d++) {
            int now = (d == 1 ? 0 : 1);
            vector<bool> picked(ans);

            for (int v : rdep[d]) {
                while (loc[p[v]] == now || picked[now]) {
                    now++;
                    if (now == ans) {
                        now = 0;
                        // if (v == rdep[d].back()) now = 0;
                    }
                }
                ops[now].push_back(v);
                loc[v] = now;
                picked[now] = 1;
                if (d == 3) cout << v << ' ' << now << endl;
            }
        }

        for (auto &i : ops) {
            cout << sz(i) << ' ';
            for (auto &j : i) cout << j << ' ';
            cout << '\n';
        }
        cout.flush();

        assert(ans == sz(ops));
    }
}
