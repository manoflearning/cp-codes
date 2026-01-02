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
constexpr int VAL = 304;

int query(const vector<int> &a) {
    assert(sz(a) <= 100'000);
    cout << "? " << sz(a) << ' ';
    for (auto &i : a) cout << i << ' ';
    cout << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    constexpr int n = 100'000;

    vector<int> w_l(n + 1), w_r(n + 1);
    for (int w = 1; w <= n; w++) {
        if (w < VAL) {
            if (!w_l[0]) w_l[0] = w;
            w_r[0] = w;
        } else {
            int x = (n + (w / VAL) - 1) / (w / VAL);
            if (!w_l[x]) w_l[x] = w;
            w_r[x] = w;
        }
    }

    for (int x = 1; x <= n; x++) {
        if (!w_l[x]) continue;
        // cout << x << ' ' << w_l[x] << ' ' << w_r[x] << '\n';
        // cout << w_r[x] - w_l[x] + 1 << '\n';
        // cout.flush();
        assert(w_r[x] - w_l[x] + 1 <= VAL);
    }

    int tc; cin >> tc;
    while (tc--) {
        vector<int> a(n, VAL);

        int res1 = query(a);

        if (res1 > 0) {
            assert(w_l[res1]);

            a.clear();
            for (int i = 1; i < VAL; i++) {
                a.push_back(w_l[res1]);
                a.push_back(i);
            }

            int res2 = query(a);
            cout << "! " << 2 * VAL - res2 - 2 + w_l[res1] << '\n';
            cout.flush();
        } else {
            a.assign(n, 1);
            int res2 = query(a);

            int w;
            for (w = 1; w < VAL; w++) {
                if ((n + w - 1) / w == res2) {
                    break;
                }
            }
            assert(w < VAL);

            cout << "! " << w << '\n';
            cout.flush();
        }
    }
}