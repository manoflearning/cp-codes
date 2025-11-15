#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    string x; cin >> x;

    int rem_len = max(0, sz(x) - 10);

    ll xp = stoll(x.substr(0, min(10, sz(x))));

    map<ll, ll> ans;
    for (ll p = 2; p * p <= xp; p++) {
        if (xp % p) continue;

        while (xp % p == 0) {
            ans[p]++;
            xp /= p;
        }
    }
    if (xp > 1) ans[xp]++;

    if (rem_len) {
        ans[2] += rem_len;
        ans[5] += rem_len;
    }

    cout << sz(ans) << '\n';
    for (auto &[k, v] : ans) {
        cout << k << ' ' << v << '\n';
    }
}