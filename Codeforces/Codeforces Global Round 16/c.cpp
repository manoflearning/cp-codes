#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
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

        vector<string> a(2);
        for (auto &i : a) cin >> i;
        
        vector<bool> used(n);

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[0][i] == '0' && a[1][i] == '1') {
                ans += 2;
            } else if (a[0][i] == '1' && a[1][i] == '0') {
                ans += 2;
            } else if (a[0][i] == '0' && a[1][i] == '0') {
                bool can_make_2 = 0;
                if (0 < i && a[0][i - 1] == '1' && a[1][i - 1] == '1' && !used[i - 1]) {
                    can_make_2 = 1;
                    used[i - 1] = 1;
                } else if (i + 1 < n && a[0][i + 1] == '1' && a[1][i + 1] == '1') {
                    can_make_2 = 1;
                    used[i + 1] = 1;
                }

                ans += (can_make_2 ? 2 : 1);
            }
        }

        cout << ans << '\n';
    }
}