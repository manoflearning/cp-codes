#pragma GCC optimize ("Ofast, unroll-loops")
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
        int n, c;
        cin >> n >> c;

        vector<bool> vis(c + 1);
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            vis[x] = 1;
        }

        bool yes = 1;
        yes &= vis[1];

        vector<int> ps(2 * c + 1);
        for (int i = 1; i <= 2 * c; i++)
            ps[i] = (i <= c ? vis[i] : 0) + ps[i - 1];

        for (int i = 2; i <= c; i++) { // time: O(c log c)
            if (!vis[i]) continue;

            for (int j = 2; j <= c / i; j++) {
                yes &= vis[j] || (ps[(j + 1) * i - 1] - ps[j * i - 1] == 0);
            }
        }

        cout << (yes ? "Yes" : "No") << '\n';
    }
}
