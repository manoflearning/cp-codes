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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n), cnt(n + 1);
        for (auto &i : a) {
            cin >> i;
            cnt[i]++;
        }

        int ans = -1;
        int cnt1 = 1;
        for (int i = 0; i <= n; i++) {
            if (cnt[i] >= 2) continue;
            if (cnt[i] == 0) {
                ans = i;
                break;
            }
            if (cnt[i] == 1) {
                if (cnt1 == 0) { ans = i; break; }
                cnt1--;
            }
        }

        cout << ans << '\n';
    }
}
