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
#define rall(x) (x).rbegin(), (x).rend()

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<int> l(n + 2, INF), r(n + 2);
        for (int i = 1; i <= n; i++) {
            l[a[i]] = min(l[a[i]], i);
            r[a[i]] = max(r[a[i]], i);
        }

        bool is_valid = 1;
        for (int t = 1; t <= n; t++) {
            l[t] = min(l[t], l[t - 1]);
            r[t] = max(r[t], r[t - 1]);
            // if (l[t] == INF) continue;
            // cout << t << ' ' << l[t] << ' ' << r[t] << '\n';
            if (t < r[t] - l[t] + 1) is_valid = 0;
        }

        if (!is_valid) {
            cout << 0 << '\n';
            continue;
        }

        vector<int> psum(n + 2);
        int cnt = 0;
        for (int t = 1; t <= n; t++) {
            if (l[t] == INF) continue;
            cnt++;
            psum[max(1, r[t] - t + 1)]++;
            psum[min(n + 1, l[t] + t)]--;
            // psum[l[t]]++, psum[r[t] + 1]--;
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            psum[i] += psum[i - 1];
            ans += (psum[i] == cnt);
        }

        cout << ans << '\n';
    }
}
