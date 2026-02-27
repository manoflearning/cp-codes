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

        vector<string> s(2);
        for (auto &i : s) cin >> i;

        bool non = 0, mul = 0;

        vector<vector<bool>> vis(2, vector<bool>(n));
        int prv = -5;
        for (int i = 0; i < n; i++) {
            bool x0{}, x1{};
            x0 = (s[0][i] != '#' && !vis[0][i]);
            x1 = (s[1][i] != '#' && !vis[1][i]);

            if (x0 && x1) {
                if (prv + 1 == i) mul = 1;

                vis[0][i] = vis[1][i] = 1;
                prv = i;
            } else if (x0) {
                if (i + 1 < n && s[0][i + 1] != '#' && !vis[0][i + 1]) {
                    vis[0][i] = vis[0][i + 1] = 1;
                } else {
                    non = 1;
                }
            } else if (x1) {
                if (i + 1 < n && s[1][i + 1] != '#' && !vis[1][i + 1]) {
                    vis[1][i] = vis[1][i + 1] = 1;
                } else {
                    non = 1;
                }
            }
        }

        if (non) cout << "None\n";
        else if (mul) cout << "Multiple\n";
        else cout << "Unique\n";
    }
}
