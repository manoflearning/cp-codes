#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll k; cin >> k;

    ll ans1 = 0, ans2 = 0;
    for (ll i = 1; i * i <= k * k; i++) {
        if ((k * k) % i) continue;
        ll j = (k * k) / i;

        ll a = -1, b = -1;
        {
            a = i + k;
            b = j + k;
            ans1++, ans2 += a + b;
        }
        {
            a = -i + k;
            b = -j + k;
            ans1++, ans2 += a + b;
        }
    }

    cout << ans1 << ' ' << ans2;

    // ll z; cin >> z;

    // auto check = [&](ll x) {
    //     ll k = x * (x + 4 * z);
    //     ll sq = -1;
    //     {
    //         ll l = 1, r = k;
    //         while (l < r) {
    //             ll mid = (l + r) >> 1;
    //             if (mid * mid < k) l = mid + 1;
    //             else r = mid;
    //         }
    //         sq = l;
    //     }
    //     return sq * sq == k;
    // };

    // ll cnt = 0;
    // for(ll i = 0; i <= 1e6; i++) {
    //     if(check(i)) {cout << i << '\n'; cnt++;}
    // }
    // cout << '\n';
    // cout << cnt << '\n';
}
