#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// struct UF {
//     vector<int> e;
//     UF(int n) { e.assign(n, -1); }
//     int find(int x) {
//         if (e[x] < 0) return x;
//         return e[x] = find(e[x]);
//     }
//     void merge(int u, int v) {
//         u = find(u), v = find(v);
//         if (u == v) return;
//         e[u] = v;
//     }
// };

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n), b(n);
        for (auto &i : a) cin >> i, i--;
        for (auto &i : b) cin >> i, i--;

        vector<int> ra(n), rb(n);
        for (int i = 0; i < n; i++) {
            ra[a[i]] = i;
            rb[b[i]] = i;
        }

        vector<pii> ans;

        bool yes = 1;
        for (int k = 0; k < n; k++) {
            const int x = b[k];

            vector<int> idxs(1, k);
            for (int j = k + 1; j <= ra[x]; j++) {
                if (a[idxs.back()] < a[j] && a[j] <= a[ra[x]]) {
                    idxs.push_back(j);
                }
            }

            for (int i = 0; i + 1 < sz(idxs); i++) {
                ans.push_back({idxs[0], idxs[i + 1]});
                ra[a[idxs[0]]] = idxs[i + 1];
                ra[a[idxs[i + 1]]] = idxs[0];
                swap(a[idxs[0]], a[idxs[i + 1]]);
            }

            if (a[k] != b[k]) { yes = 0; break; }
        }

        if (yes) {
            cout << "YES\n";
            cout << sz(ans) << '\n';
            for (const auto [u, v] : ans) {
                cout << u + 1 << ' ' << v + 1 << '\n';
            }
        } else {
            cout << "NO\n";
        }
    }
}