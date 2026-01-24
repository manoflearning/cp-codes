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
        int n, m;
        string s;
        cin >> n >> m >> s;

        vector<int> row(n * m), col(n * m);

        vector<int> ps(n * m);
        for (int t = 0; t < n * m; t++) {
            ps[t] = (s[t] == '1') + (t > 0 ? ps[t - 1] : 0);
            if (t < m) row[t] = ps[t] > 0;
            else row[t] = (ps[t] - ps[t - m] > 0) + row[t - m];
        }

        int cnt = 0;
        vector<bool> vis(m);
        for (int t = 0; t < n * m; t++) {
            if (s[t] == '1') {
                if (!vis[t % m]) {
                    vis[t % m] = 1;
                    cnt++;
                }
            }
            col[t] = cnt;
        }

        for (int t = 0; t < n * m; t++)
            cout << row[t] + col[t] << ' ';
        cout << '\n';
    }
}
