#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n; cin >> n;

    ll ans = 0;
    for (ll i = 1; ; i++) {
        ll flag = 1;
        for (flag = 1; flag <= i; flag *= 10);
        flag /= 10;

        ll j = 0;
        for (ll k = 1; k <= flag; k *= 10) {
            j += (flag / k) * (i / k % 10);
        }

        ll x1 = i * flag * 10 + j;
        if (x1 <= n) ans++;

        j = 0;
        for (ll k = 10; k <= flag; k *= 10) {
            j += (flag / k) * (i / k % 10);
        }

        ll x2 = i * flag + j;
        if (x2 <= n) ans++;

        if (x1 > n && x2 > n) break;

        // cout << i << ' ' << x1 << ' ' << x2 << '\n';
    }

    cout << ans;
}
