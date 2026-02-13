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
    int n_set{};
    UF(int n) { e.assign(n, -1); n_set = n; }
    int find(int x) {
        if (e[x] < 0) return x;
        return e[x] = find(e[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        e[u] += e[v], e[v] = u;
        n_set--;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    UF uf(n), uf_r(n), uf_b(n);
    int cnt = 0, cnt_r = 0, cnt_b = 0;
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        u--, v--;

        uf.merge(u, v), cnt++;
        if (t == 1) uf_r.merge(u, v), cnt_r++;
        if (t == 2) uf_b.merge(u, v), cnt_b++;

        const int mx = cnt - (n - uf.n_set);
        const int mx_r = cnt_r - (uf_b.n_set - uf.n_set);
        const int mx_b = cnt_b - (uf_r.n_set - uf.n_set);

        cout << 2 * min({mx_r, mx_b, mx / 2}) << '\n';
    }
}
