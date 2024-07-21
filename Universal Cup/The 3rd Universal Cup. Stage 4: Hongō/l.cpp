#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
        vector<ll> a(n);
        for (auto& i : a) cin >> i;

        sort(all(a));

        ll ans = -1;
        for (int i = 0; i + 2 < n; i++) {
            if (a[i + 2] - a[i + 1] < a[i]) {
                ll x = (a[i] + a[i + 1] + a[i + 2]) / 2;
                ll res = x * (x - a[i]) * (x - a[i + 1]) * (x - a[i + 2]);
                ans = max(ans, res);
            }
        }

        cout << ans << '\n';
    }
}