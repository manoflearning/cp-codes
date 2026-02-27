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
    UF(int n) : e(n, -1) {}
    int find(int x) {
        if (e[x] < 0) return x;
        return e[x] = find(e[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        e[u] += e[v];
        e[v] = u;
    }
    int size(int i) { return -e[find(i)]; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    UF uf(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        uf.merge(u, v);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, uf.size(i));

    cout << ans << '\n';
}
