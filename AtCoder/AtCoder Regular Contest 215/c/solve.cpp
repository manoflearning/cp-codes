#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> x(n), y(n), z(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i] >> z[i];
        }

        vector<int> ord(n);
        iota(all(ord), 0);
        
        unordered_set<int> st;
        int mn_x = INF, mn_y = INF, mn_z = INF;
        auto update = [&]() {
            st.insert(ord[0]);
            mn_x = min(mn_x, x[ord[0]]);
            mn_y = min(mn_y, y[ord[0]]);
            mn_z = min(mn_z, z[ord[0]]);

            for (const int i : ord) {
                if (mn_x <= x[i] || mn_y <= y[i] || mn_z <= z[i]) {
                    st.insert(i);
                    mn_x = min(mn_x, x[i]);
                    mn_y = min(mn_y, y[i]);
                    mn_z = min(mn_z, z[i]);
                }
            }
        };

        sort(all(ord), [&](int i, int j) { return x[i] > x[j]; });
        update();
        sort(all(ord), [&](int i, int j) { return y[i] > y[j]; });
        update();
        sort(all(ord), [&](int i, int j) { return z[i] > z[j]; });
        update();

        cout << sz(st) << '\n';
    }

    return 0;
}
