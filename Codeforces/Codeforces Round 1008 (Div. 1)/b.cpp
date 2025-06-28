#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll pow2[33];

ll query(ll n) {
    cout << n << '\n';
    cout.flush();

    ll ret; cin >> ret;
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    // cout << (12430 | 12345) + (12430 | 24690) << '\n';

    pow2[0] = 1;
    for (int i = 1; i < 33; i++) {
        pow2[i] = 2 * pow2[i - 1];
    }

    int tc; cin >> tc;
    while (tc--) {
        ll n1 = 0, n2 = 0;
        for (int i = 0; i < 30; i++) {
            if (i & 1) n1 |= (1 << i);
            else n2 |= (1 << i);
        }

        ll w1 = query(n1) - 2 * n1;
        ll w2 = query(n2) - 2 * n2;
        w2 /= 2;

        cout << "!\n";
        cout.flush();
        
        vector<ll> res(33);
        for (int i = 0; i < 30; i++) {
            if (!(i & 1)) {
                res[i] += w1 % 4 * (1 << i);
                w1 /= 4;
            } else {
                res[i] += w2 % 4 * (1 << i);
                w2 /= 4;
            }
        }

        ll m; cin >> m;

        ll ans = 0;
        for (int i = 0; i < 30; i++) {
            if ((1 << i) & m) {
                ans += 2 * (1 << i);
            } else ans += res[i];
        }

        cout << ans << '\n';
        cout.flush();
    }
}
