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

        for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
        cout << '\n';
    }
}
