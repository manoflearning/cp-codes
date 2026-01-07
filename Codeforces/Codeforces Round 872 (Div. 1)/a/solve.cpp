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
        int n, m;
        cin >> n >> m;

        int cnt0 = 0, cnt1 = 0, cnt2 = 0;

        vector<int> vis(m + 2), psum(m + 2);
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            if (x > 0) {
                if (vis[x]) continue;
                vis[x] = psum[x] = 1;
                cnt0++;
            } else {
                if (x == -1) cnt1++;
                else cnt2++;
            }
        }

        for (int i = 1; i <= m; i++)
            psum[i] += psum[i - 1];
        
        int ans = 0;
        
        ans = max(ans, cnt0 + min(m - cnt0, max(cnt1, cnt2)));

        int lb = 1, ub = 1;
        for (int i = 1; i <= m; i++) {
            if (!vis[i]) continue;

            while (lb < i) {
                if (vis[lb]) {
                    lb++;
                    continue;
                }

                const int diff = (i - lb) - (psum[i - 1] - psum[lb - 1]);
                if (diff > cnt1) lb++;
                else break;
            }
            while (ub < i) ub++;
            while (ub < m) {
                const int diff = (ub - i) - (psum[ub] - psum[i]);
                if (diff < cnt2) ub++;
                else break;
            }

            int res = 1;

            res += i - lb;
            res += ub - i;
            
            res += psum[lb - 1];
            res += psum[m] - psum[ub];

            ans = max(ans, res);
        }

        cout << ans << '\n';
    }
}