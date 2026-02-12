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
        ll p, q;
        cin >> p >> q;

        ll l = 0, r = min(p / 2, q / 3);
        while (l < r) {
            const ll mid = (l + r + 1) >> 1;

            const ll n = 2 * mid;
            const ll d = 3 * mid;

            const ll diff = (p - n) - (q - d);

            if (diff <= 0) l = mid;
            else r = mid - 1;
        }

        if (l == 0 || (p - 2 * l) - (q - 3 * l) != 0) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }

    return 0;
}
