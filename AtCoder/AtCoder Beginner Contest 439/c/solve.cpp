#pragma GCC optimize("Ofast")
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

    ll n; cin >> n;

    vector<ll> ans;

    vector<int> mp(n + 1);
    for (ll x = 1; ; x++) {
        if (n < x * x) break; // up to sqrt(n)
        for (ll y = x + 1; ; y++) {
            if (n < x * x + y * y) break;

            mp[x * x + y * y]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (mp[i] == 1) ans.push_back(i);
    }

    cout << sz(ans) << '\n';
    for (auto &i : ans)
        cout << i << ' ';
}
