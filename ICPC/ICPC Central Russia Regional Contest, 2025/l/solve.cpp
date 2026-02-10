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

    // for (ll n = 1000000000000000000ll, tc = 0; tc < 1000000; tc++, n--) {
    ll n; cin >> n;

    ll ansi{-1}, ansj{-1};
    for (ll i = 1; ; i++) {
        const ll j = n ^ i;
        if (!j) continue;
        if ((ll)1e18 < j) continue;

        ansi = i, ansj = j;
        break;
    }

    assert(ansi != -1);

    cout << "YES\n";
    cout << ansi << ' ' << ansj << '\n';
    // }
}
