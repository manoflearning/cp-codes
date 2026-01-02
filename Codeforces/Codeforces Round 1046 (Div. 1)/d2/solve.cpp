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

constexpr int INF = 1e9 + 7;
constexpr int W = 100'000;

int query(const vector<int> &a) {
    assert(sz(a) <= 12'500);
    cout << "? " << sz(a) << ' ';
    for (auto &i : a) cout << i << ' ';
    cout << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    constexpr int val = 105;
    constexpr int n = 12'500;

    vector<int> w_l(n + 1), w_r(n + 1);

    for (int w = 1; w <= W; w++) {
        if (w < val) {
            if (!w_l[0]) w_l[0] = w;
            w_r[0] = w;
        } else {
            int x = (n + (w / val) - 1) / (w / val);
            if (!w_l[x]) w_l[x] = w;
            w_r[x] = w;
        }
    }

    // for (int x = 1; x <= n; x++) {
    //     if (!w_l[x]) continue;
    //     cout << x << ' ' << w_l[x] << ' ' << w_r[x] << '\n';
    //     cout << w_r[x] - w_l[x] + 1 << '\n';
    //     cout.flush();
    // }

    // for (int val = 1; val <= W; val++) {
    //     w_l.assign(n + 1, 0);
    //     w_r.assign(n + 1, 0);
    //     for (int w = 1; w <= W; w++) {
    //         if (w < val) {
    //             if (!w_l[0]) w_l[0] = w;
    //             w_r[0] = w;
    //         } else {
    //             int x = (n + (w / val) - 1) / (w / val);
    //             if (!w_l[x]) w_l[x] = w;
    //             w_r[x] = w;
    //         }
    //     }

    //     bool is_valid = 1;
    //     for (int x = 1; x <= n; x++) {
    //         if (!w_l[x]) continue;
    //         // cout << x << ' ' << w_l[x] << ' ' << w_r[x] << '\n';
    //         // cout << w_r[x] - w_l[x] + 1 << '\n';
    //         // cout.flush();
    //         is_valid &= (w_r[x] - w_l[x] <= n / 2);
    //         is_valid &= (w_r[x] - w_l[x] <= w_l[x]);
    //     }

    //     if (w_l[0]) {
    //         for (int w = 1; w + 1 < val; w++) {
    //             int x1 = (n + w - 1) / w;
    //             int x2 = (n + (w + 1) - 1) / (w + 1);
    //             is_valid &= (x1 != x2);
    //         }
    //     }

    //     if (is_valid) {
    //         cout << val << '\n';
    //         cout.flush();
    //     }
    // }
    // cout << "done" << endl;

    int tc; cin >> tc;
    while (tc--) {
        vector<int> a(n, val);

        int res1 = query(a);

        if (res1 > 0) {
            a.clear();
            for (int i = 1; i <= w_r[res1] - w_l[res1]; i++) {
                a.push_back(w_l[res1]);
                a.push_back(i);
            }

            int res2 = query(a);
            cout << "! " << 2 * (w_r[res1] - w_l[res1]) - res2 + w_l[res1] << '\n';
            cout.flush();
        } else {
            a.assign(n, 1);
            int res2 = query(a);

            int w;
            for (w = 1; w < val; w++) {
                if ((n + w - 1) / w == res2) {
                    break;
                }
            }
            assert(w < val);

            cout << "! " << w << '\n';
            cout.flush();
        }
    }
}