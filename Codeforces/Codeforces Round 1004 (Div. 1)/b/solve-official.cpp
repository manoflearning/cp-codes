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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        int cnt0 = 0, lm0 = -1;
        for (int i = 0; i < n; i++) {
            cnt0 += (a[i] == 0);
            if (a[i] == 0 && lm0 == -1) lm0 = i;
        }

        vector<int> pmin(n), smex(n);
        pmin[0] = a[0];
        for (int i = 1; i < n; i++) {
            pmin[i] = min(a[i], pmin[i - 1]);
        }

        bool can_include_0 = (lm0 != -1);

        vector<bool> vis(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] > 0 || (a[i] == 0 && i == lm0)) {
                if (a[i] <= n - 1) vis[a[i]] = 1;
            }
            if (i + 1 < n) smex[i] = smex[i + 1];
            while (vis[smex[i]]) smex[i]++;

            if (i + 1 < n) {
                can_include_0 &= (pmin[i] >= smex[i + 1]);
            }
        }

        cout << (can_include_0 ? n - cnt0 + 1 : n - cnt0) << '\n';
    }
}
