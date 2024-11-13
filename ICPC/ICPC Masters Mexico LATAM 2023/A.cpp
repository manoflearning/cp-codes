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

    ll acc = 0;
    for (ll x = 1; acc < n; x++) {
        if (acc + 2 * x <= n) {
            ans += 2;
            acc += 2 * x;
        } else if (acc + x < n) {
            ans += 2;
            acc = n;
        } else {
            ans += 1;
            acc = n;
        }
    }

    cout << ans;
}
