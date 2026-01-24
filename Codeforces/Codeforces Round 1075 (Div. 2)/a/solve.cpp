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
        int n, h, l;
        cin >> n >> h >> l;

        if (h > l) swap(h, l);

        int cnt1 = 0, cnt2 = 0;
        vector<int> a(n);
        for (auto &i : a) {
            cin >> i;

            if (i <= h) cnt1++;
            else if (i <= l) cnt2++;
        }

        int ans = 0;
        const int mn = min(cnt1, cnt2);
        ans += mn;
        cnt1 -= mn, cnt2 -= mn;
        ans += cnt1 / 2;
        cout << ans << '\n';
    }
}
