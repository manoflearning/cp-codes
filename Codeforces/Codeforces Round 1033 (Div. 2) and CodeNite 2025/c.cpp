#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n, m;
        cin >> n >> m;

        if (m < n || n * (n + 1) / 2 < m) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> ans(n);

        ll cur = n;
        for (int v = 1; v <= n; v++) {
            ll max_diff = n - v;
            if (cur + max_diff <= m) {
                ans[n - v] = v;
                cur += max_diff;
            } else {
                ll diff = m - cur;
                ans[diff] = v;
                
                for (int i = 0, j = v + 1; i < n; i++) {
                    if (!ans[i]) ans[i] = j++;
                }
                break;
            }
        }

        cout << ans[0] << '\n';
        for (int i = 0; i + 1 < n; i++) {
            cout << ans[i] << ' ' << ans[i + 1] << '\n';
        }
    }
}
