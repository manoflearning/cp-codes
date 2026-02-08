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
        int n, k;
        cin >> n >> k;

        vector<string> a(k);
        for (auto &i : a) cin >> i;

        string ans;
        for (int d = 1; d <= n; d++) {
            if (n % d) continue;

            vector<vector<int>> cnt(d, vector<int>(26));
            for (int i = 0; i < n; i++) {
                vector<bool> vis(26);
                for (int j = 0; j < k; j++) {
                    const int x = a[j][i] - 'a';
                    if (vis[x]) continue;
                    vis[x] = 1;
                    cnt[i % d][x]++;
                }
            }

            bool res = 1;
            string tmp;
            for (int i = 0; i < d; i++) {
                bool yes = 0;
                int opt = -1;
                for (int j = 0; j < 26; j++) {
                    if (cnt[i][j] == n / d) {
                        yes = 1;
                        opt = j;
                        break;
                    }
                }

                if (yes) {
                    tmp.push_back(opt + 'a');
                } else {
                    res = 0;
                    break;
                }
            }

            if (res) {
                int cnt = n / d;
                while (cnt--) ans += tmp;
                break;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}

