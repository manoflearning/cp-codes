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
        int n; cin >> n;

        vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) {
            cin >> l[i] >> r[i];
        }

        vector<bool> vis(n);
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; i--) {
            int opt = -1, opt_score = -1e9;

            for (int j = n - 1; j >= 0; j--) {
                if (vis[j]) continue;

                // int score = r[j] - l[j] - 1;
                int score = 0;

                for (int k = 0; k < n; k++) {
                    if (vis[k] || j == k) continue;

                    score += (l[k] < l[j] && l[j] < r[k]);
                    score += (l[k] < r[j] && r[j] < r[k]);
                }

                if (opt_score < score) {
                    opt = j;
                    opt_score = score;
                }
            }

            vis[opt] = 1;
            ans[i] = opt;
        }

        for (auto &i : ans) cout << i + 1 << ' ';
        cout << '\n';
    }
}
