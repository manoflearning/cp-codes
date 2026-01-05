#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;
        
        sort(all(a));
        sort(all(b));

        ll ans = 1;

        ll cnt = 0;
        int j = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            while (j >= 0 && a[j] > b[i]) cnt++, j--;

            if (cnt <= 0) {
                ans = 0;
                break;
            }
            ans = ans * cnt % MOD;
            cnt--;
        }

        cout << ans << '\n';
    }
}