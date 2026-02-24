#pragma GCC optimize ("O3")
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

    int n; cin >> n;

    vector<ll> a(n), b(n);
    ll sum_a = 0, sum_b = 0;
    for (auto &i : a) cin >> i, sum_a += i;
    for (auto &i : b) cin >> i, sum_b += i;

    // if (sum_a > sum_b) {
    //     cout << -1 << '\n';
    //     exit(0);
    // }

    int l = 0, r = n;
    while (l < r) {
        const int mid = (l + r) >> 1;

        bool yes = 1;
        vector<ll> c = b;
        int j = 0;
        for (int i = 0; i < n; i++) {
            ll x = a[i];
            j = max(j, i - mid);
            while (x && j < n && j <= i + mid) {
                const ll both = min(x, c[j]);
                x -= both, c[j] -= both;
                if (!c[j]) j++;
            }
            if (x) { yes = 0; break; }
        }

        if (yes) r = mid;
        else l = mid + 1;
    }

    cout << (l == n ? -1 : l) << '\n';
}