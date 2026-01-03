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

    int n; cin >> n;

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    ll ans = 0;

    map<int, ll> mp;
    for (auto &i : a) {
        mp[i]++;

        if (i % 5 == 0) {
            ll res = mp[i / 5 * 3] * mp[i / 5 * 7];
            ans += res;
        }
    }

    mp.clear();
    reverse(all(a));

    for (auto &i : a) {
        mp[i]++;

        if (i % 5 == 0) {
            ll res = mp[i / 5 * 3] * mp[i / 5 * 7];
            ans += res;
        }
    }

    cout << ans;
}
