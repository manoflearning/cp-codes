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

int query(int i, int j) {
    cout << "? " << i << ' ' << j << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        
        vector<int> x(n + 1);
        
        vector<int> vis(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> x[i];
            vis[x[i]] = i;
        }

        int ans = 0;

        int j = -1;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) { j = i; break; }
        }

        if (j != -1) {
            int res = query(j, j % n + 1);
            if (res == 0) ans = 1;
            else ans = 2;
        } else {
            int res1 = query(vis[1], vis[n]);
            int res2 = query(vis[n], vis[1]);
            if (res1 >= n - 1 && res2 >= n - 1) ans = 2;
            else ans = 1;
        }

        cout << "! ";
        cout << (ans == 1 ? "A" : "B") << '\n';
        cout.flush();
    }
}
