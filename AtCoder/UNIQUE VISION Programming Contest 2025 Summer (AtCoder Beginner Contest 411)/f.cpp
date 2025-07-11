#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int ans;

struct UF {
    vector<int> uf;
    vector<unordered_set<int>> e;
    void build(int n) {
        uf.resize(n + 1, -1);
        e.resize(n + 1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;

        if (sz(e[U]) > sz(e[V])) swap(U, V);

        uf[U] = V;

        for (auto &i : e[U]) {
            e[i].erase(U);
            ans--;

            if (i != V && !e[i].count(V)) {
                e[i].insert(V);
                e[V].insert(i);
                ans += 2;
            }
        }

        ans -= sz(e[U]);
        e[U].clear();
    }
} uf;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    uf.build(n);

    vector<pii> e(m);
    for (auto &[u, v] : e) {
        cin >> u >> v;
        uf.e[u].insert(v);
        uf.e[v].insert(u);
    }

    ans = 2 * m;

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        x--;

        auto [u, v] = e[x];
        int U = uf.find(u);
        int V = uf.find(v);
        if (U != V && uf.e[U].count(V)) {
            uf.merge(U, V);
        }

        assert(ans % 2 == 0);

        cout << ans / 2 << '\n';
    }
}
