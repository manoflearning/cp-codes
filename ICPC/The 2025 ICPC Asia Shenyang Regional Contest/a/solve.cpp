#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using i128 = __int128_t;
using pii = pair<int, int>;
using vi = vector<int>;

i128 gcd(i128 x, i128 y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll _n, _k, _a, _b;
    cin >> _n >> _k >> _a >> _b;

    const i128 n = _n, k = _k, a = _a, b = _b;

    i128 l = 1, r = 1e19;
    while (l < r) {
        const i128 mid = (l + r) / 2;

        i128 cnt = 0;
        i128 d = 1;
        for (; ; d++) {
            const i128 ub = (mid / d - 2 * b) / a;

            const i128 i = min(n - d, (ub - d) / 2);
            const i128 j = i + d;

            cnt += i;
            if (i < 1) break;
            if (cnt >= k) break;
        }

        // cout << (ll)mid << ' ' << (ll)d << '\n';

        if (cnt >= k) r = mid;
        else l = mid + 1;
    }

    const i128 g = gcd(l, a);
    cout << (ll)(l / g) << ' ' << (ll)(a / g) << '\n';
}
