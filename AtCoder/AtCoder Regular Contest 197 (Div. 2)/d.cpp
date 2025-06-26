#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int N = 404;

struct UF {
    vector<int> uf;
    void build(int N) {
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
        uf[V] = U;
    }
} uf;

int n, a[N][N];
ll fac[N];

ll f(vector<int> vs) {
    // DEBUG
    // cout << sz(vs) << '\n';
    // for (auto v : vs) cout << v << ' ';
    // cout << '\n';

    vector<int> deg(N);
    for (int v : vs) for (int u : vs) if (v != u && a[u][v]) deg[v]++;

    vector<bool> is_ro(N);
    vector<int> ro;
    if (sz(vs) == n) {
        ro.push_back(0);
        is_ro[0] = 1;
    } else {
        for (int v : vs) {
            if (deg[v] == sz(vs) - 1) {
                ro.push_back(v);
                is_ro[v] = 1;
            }
        }
    }

    ll ret = fac[sz(ro)];

    // base case
    if (ro.empty()) return 0;
    if (sz(ro) == sz(vs)) return ret;

    // inductive step
    uf.build(N);

    for (int v : vs) {
        if (is_ro[v]) continue;
        for (int u : vs) {
            if (v == u) continue;
            if (is_ro[u]) continue;

            if (a[u][v]) uf.merge(u, v);
        }
    }

    vector<vector<int>> vs_nxt;
    vector<int> vs_nxt_idx(N, -1);
    for (int v : vs) {
        if (is_ro[v]) continue;
        for (int u : vs) {
            if (v <= u) continue;
            if (is_ro[u]) continue;

            if (uf.find(u) == uf.find(v)) {
                vs_nxt[vs_nxt_idx[u]].push_back(v);
                vs_nxt_idx[v] = vs_nxt_idx[u];
                break;
            }
        }
        if (vs_nxt_idx[v] == -1) {
            vs_nxt.push_back({v});
            vs_nxt_idx[v] = sz(vs_nxt) - 1;
        }
    }

    for (auto &i : vs_nxt) {
        ret = ret * f(i) % MOD;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = i * fac[i - 1] % MOD;
    }

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }

        bool is_valid = 1;
        for (int i = 0; i < n; i++) {
            is_valid &= (a[0][i] == 1);
            is_valid &= (a[i][i] == 1);
            for (int j = 0; j < n; j++) {
                is_valid &= (a[i][j] == a[j][i]);
            }
        }

        if (!is_valid) {
            cout << 0 << '\n';
            continue;
        }

        vector<int> v(n);
        iota(all(v), 0);

        cout << f(v) << '\n';
    }    
}
