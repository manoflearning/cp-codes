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
#define rall(x) (x).rbegin(), (x).rend()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<ll> pow10(10);
    pow10[0] = 1;
    for (int i = 1; i < 10; i++) {
        pow10[i] = 10 * pow10[i - 1];
    }

    int tc; cin >> tc;
    while (tc--) {
        int A, B, C;
        ll k;
        cin >> A >> B >> C >> k;

        const ll lb_a = pow10[A - 1], ub_a = pow10[A] - 1;
        const ll lb_b = pow10[B - 1], ub_b = pow10[B] - 1;
        const ll lb_c = pow10[C - 1], ub_c = pow10[C] - 1;

        ll ansa = -1, ansb = -1, ansc = -1;

        ll rem = k;
        for (ll a = lb_a; a <= ub_a; a++) {
            ll lb = max(lb_b, lb_c - a);
            ll rb = min(ub_b, ub_c - a);
            if (lb > rb) continue;
            ll lc = max(lb_c, a + lb_b);
            ll rc = min(ub_c, a + ub_b);
            if (lc > rc) continue;
            
            ll res = min(rb - lb + 1, rc - lc + 1);
            if (rem <= res) {
                ll b = lb + rem - 1;
                ll c = a + b;
                ansa = a, ansb = b, ansc = c;
                break;
            }
            rem -= res;
        }

        if (ansa != -1) {
            cout << ansa << " + " << ansb << " = " << ansc << '\n';
        } else {
            cout << -1 << '\n';
        }

        // ll rem = k;
        // for (ll c = pow10[C - 1]; c < pow10[C]; c++) {
        //     ll la = max(lb_a, c - ub_b);
        //     ll ra = min(ub_a, c - lb_b);
        //     if (la > ra) continue;
        //     ll lb = max(lb_b, c - ub_a);
        //     ll rb = min(ub_b, c - lb_a);
        //     if (lb > rb) continue;
            
        //     ll res = min(ra - la + 1, rb - lb + 1);
        //     cout << c << ' ' << res << '\n';
        //     if (rem <= res) {
        //         ll a = la + rem - 1;
        //         ll b = c - a;
        //         cout << a << " + " << b << " = " << c << '\n';
        //         break;
        //     }
        //     rem -= res;
        // }
    }
}
