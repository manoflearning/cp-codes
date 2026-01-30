#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

struct DSU {
    vector<int> uf;
    DSU(int n) {
        uf.assign(n, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        uf[u] = v;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        vector<int> b = a;
        sort(all(b));

        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return a[i] < a[j];
        });

        // unordered_map<int, int> mp;
        // for (int i = 0; i < n; i++) mp[b[i]] = i;

        int l = 0, r = INF;
        while (l < r) {
            const int mid = (l + r + 1) >> 1;

            bool yes = 1;
            
            // DSU uf(n);
            // for (int i = 0; i < n; i++) {
            //     if (b[i] - b[0] >= mid) uf.merge(0, i);
            //     if (b[n - 1] - b[i] >= mid) uf.merge(i, n - 1);
            // }

            for (int i = 0; i < n; i++) {
                if (a[i] == b[i]) continue;

                bool res1 = 0;
                res1 |= a[i] - b[0] >= mid;
                res1 |= b[n - 1] - a[i] >= mid;

                bool res2 = 0;
                res2 |= b[i] - b[0] >= mid;
                res2 |= b[n - 1] - b[i] >= mid;

                yes &= res1 && res2;
            }

            if (!yes) r = mid - 1;
            else l = mid;
        }

        cout << (l == INF ? -1 : l) << '\n';
    }
}
