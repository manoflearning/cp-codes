#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// optional<vector<vector<int>>> naive(int n) {
//     vector<vector<int>> ret;
//     vector<int> p(n);
//     iota(all(p), 1);
//     do {
//         bool yes = 1;
//         unordered_set<int> st;
//         st.insert(p[n - 1]);
//         for (int i = n - 2; i >= 0; i--) {
//             st.insert(p[i]);
//             yes &= st.count(p[i] ^ (i + 1));
//             if (!yes) break;
//         }
//         if (yes) ret.push_back(p);
//     } while (next_permutation(all(p)));
//     if (!ret.empty()) return ret;
//     else return nullopt;
// }

// bool verify(int n, const vector<int> &ans) {
//     set<int> st;
//     vector<bool> vis(n + 1);
//     vis[ans[n]] = 1;
//     st.insert(ans[n]);
//     for (int i = n - 1; i >= 1; i--) {
//         if (!vis[ans[i] ^ i]) {
//             return 0;
//         }
//         vis[ans[i]] = 1;
//         st.insert(ans[i]);
//     }
//     if (sz(st) < n) return 0;
//     return 1;
// }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // for (int n = 4; n <= 100; n += 2) {
    //     auto res = naive(n);
    //     if (res) {
    //         cout << "n = " << n << '\n';
    //         for (auto &i : *res) {
    //             for (auto &j : i) cout << j << ' ';
    //             cout << '\n';
    //         }
    //         cout << '\n';
    //         cout.flush();
    //     } else {
    //         cout << "n = " << n << '\n';
    //         cout << -1 << '\n';
    //         cout.flush();
    //     }
    // }

    int tc; cin >> tc;
    while (tc--) {
    // for (int _n = 4; _n <= 10'000; _n++) {
    //     int n = _n;

        int n; cin >> n;
        
        vector<int> ans(n + 1);
        vector<bool> vis(n + 1);
        for (int i = 2; i <= n - 1; i++) {
            ans[i] = i ^ 1;
            vis[ans[i]] = 1;
        }
        ans[n] = 1;
        vis[ans[n]] = 1;

        for (int i = 1; i <= n; i++) {
            if (!vis[i]) { ans[1] = i; break; }
        }

        bool yes = 1;
        if (!(n & 1)) {
            vis.assign(n + 1, 0);
            vis[ans[n]] = 1;

            yes = 0;
            for (int i = n - 1; i >= 2; i--) {
                const int x1 = ans[i] ^ 1;
                const int x2 = ans[1] ^ i;

                bool res = 1;
                res &= (1 <= x1 && x1 <= n);
                res &= (x2 <= n && vis[x2]);

                if (res) {
                    yes = 1;
                    swap(ans[1], ans[i]);
                    break;
                }

                vis[ans[i]] = 1;
            }
        }

        if (yes) {
            for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
            cout << '\n';

            // if (!verify(n, ans)) {
            //     cout << n << '\n';
            //     for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
            //     assert(0);
            // }
        } else {
            cout << -1 << '\n';
        }
    }
}
