#pragma GCC optimize ("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct UF {
    vector<int> e;
    int n_comps{};
    UF(int n) { e.assign(n, -1); n_comps = n; }
    int find(int x) {
        if (e[x] < 0) return x;
        return e[x] = find(e[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        e[u] = v;
        n_comps--;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m, q;
        cin >> n >> m >> q;

        const int mod = n;
        const ll p = n;

        unordered_set<ll> e;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            e.insert(u * p + v);
        }

        vector<pii> qu(q);
        for (auto &i : qu) {
            cin >> i.first >> i.second;
        }

        vector<int> pow2(q), pow3(q), pp2(q), pp3(q);
        pow2[1] = pow3[1] = pp2[1] = pp3[1] = 1;
        for (int i = 1; i + 1 < q; i++) {
            pow2[i + 1] = 2 * pow2[i] % mod;
            pow3[i + 1] = 3 * pow3[i] % mod;
            pp2[i + 1] = (pow2[i + 1] + pp2[i]) % mod;
            pp3[i + 1] = (pow3[i + 1] + pp3[i]) % mod;
        }

        unordered_map<ll, int> e2;
        vector<pii> qu_e(q);
        for (int i = q - 1; i >= 0; i--) {
            const auto [a, b] = qu[i];

            int u = (pp2[i] + a) % mod;
            int v = (pp3[i] + b) % mod;
            if (u > v) swap(u, v);
            qu_e[i] = {u, v};
            if (e.count(u * p + v)) e2[u * p + v]++;
        }

        UF uf(n);
        for (const auto h : e) {
            const int u = h / p, v = h % p;
            if (!e2.count(u * p + v)) uf.merge(u, v);
        }

        int idx = q;
        for (int i = q - 1; i >= 0; i--) {
            const auto [u, v] = qu_e[i];

            // cout << i << ' ' << u << ' ' << v << ' ' << uf.n_comps << '\n';

            if (uf.n_comps > 1) idx = i;
            if (e.count(u * p + v)) {
                e2[u * p + v]--;
                if (e2[u * p + v] == 0) uf.merge(u, v);
            }
        }

        for (int i = 0; i < idx; i++) cout << 1 << '\n';
        for (int i = idx; i < q; i++) cout << 0 << '\n';
    }
}