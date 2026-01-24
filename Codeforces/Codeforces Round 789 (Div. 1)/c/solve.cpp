#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> ca(n), cb(n);
        for (auto &i : ca) cin >> i;
        for (auto &i : cb) cin >> i;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[ca[i] - 1] = cb[i] - 1;
        }

        vector<int> ls;
        vector<bool> vis(n);
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            
            int l = 0;
            int now = i;
            while (!vis[now]) {
                vis[now] = 1;
                // cout << now << ' ' << a[now] << '\n';
                l++;
                now = a[now];
            }
            if (l > 1) ls.push_back(l - (l & 1));
        }

        sort(all(ls));

        ll ans = 0;

        int lb = 1, ub = n;
        for (int l : ls) {
            vector<int> arr;
            for (int i = 0; i < l; i++) {
                if (~i & 1) arr.push_back(lb++);
                else arr.push_back(ub--);
            }

            for (int i = 0; i < sz(arr); i++) {
                ans += abs(arr[(i + 1) % sz(arr)] - arr[i]);
            }
        }

        cout << ans << '\n';
    }
}
