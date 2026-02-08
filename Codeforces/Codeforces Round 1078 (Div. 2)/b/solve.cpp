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
        int n;
        ll x, y;
        cin >> n >> x >> y;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll sum = 0;
        for (auto &i : a) {
            sum += i / x * y;
        }

        ll ans = 0;
        for (auto &i : a) {
            ans = max(ans, sum - i / x * y + i);
        }

        cout << ans << '\n';
    }

    return 0;
}

