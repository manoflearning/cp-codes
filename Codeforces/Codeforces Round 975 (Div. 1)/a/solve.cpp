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

    int tc; cin >> tc;
    while (tc--) {
        int n; ll k;
        cin >> n >> k;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        sort(rall(a));

        vector<ll> sa(n);
        sa[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            sa[i] = a[i] + sa[i + 1];
        }

        // ll l = 1, r = n;
        for (int x = n; x >= 1; x--) {
            ll mid = x;

            ll res = 0;

            ll sum_a = sa[0];

            if (mid * a[0] > sum_a) {
                res += mid * a[0] - sum_a;
                sum_a += mid * a[0] - sum_a;
            }

            if (sum_a % mid) {
                ll fuck = mid - sum_a % mid;
                res += fuck;
            }

            if (res <= k) {
                cout << x << '\n';
                break;
            }
        }
    }
}
