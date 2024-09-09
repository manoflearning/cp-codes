#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll check_even(ll n, ll mid, bool print) {
    vector<ll> x(n), y(n);
    x[0] = y[0] = 2 * mid;
    for (int i = 1; i < n; i++) {
        y[i] += y[i - 1] / 2;
        if ((y[i] + x[i - 1]) % 2 == i % 2) {
            x[i] = x[i - 1];
        } else {
            x[i] = x[i - 1] - 1;
        }
        y[i] += x[i];
        if (x[i] < 0 || y[i] < 0) return 0;
    }

    if (print) {
        for (auto& i : x) cout << i << ' ';
        cout << '\n';
    }

    return y[n - 1];
}

ll check_odd(ll n, ll mid) {
    vector<ll> x(n), y(n);
    x[0] = y[0] = 2 * mid - 1;
    for (int i = 1; i < n; i++) {
        y[i] += y[i - 1] / 2;
        if ((y[i] + x[i - 1]) % 2 != i % 2) {
            x[i] = x[i - 1];
        } else {
            x[i] = x[i - 1] - 1;
        }
        y[i] += x[i];
        if (x[i] < 0 || y[i] < 0) return 0;
    }
    return y[n - 1];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // ll n; cin >> n;

    // if (n & 1) {
    //     ll l = 1, r = n;
    //     while (l < r) {
    //         ll mid = (l + r) >> 1;

    //         if (check_odd(n, mid) >= 1) r = mid;
    //         else l = mid + 1;
    //     }
    //     if (check_odd(n, l) == 1) cout << 2 * l - 1;
    //     else cout << 0;
    // } else {
    //     ll l = 1, r = n;
    //     while (l < r) {
    //         ll mid = (l + r) >> 1;

    //         if (check_even(n, mid) >= 1) r = mid;
    //         else l = mid + 1;
    //     }

    //     if (check_even(n, l) == 1) cout << 2 * l;
    //     else cout << 0;
    // }

    for (int i = 2; i <= 1000; i += 2) {
        ll l = 1, r = i;
        while (l < r) {
            ll mid = (l + r) >> 1;

            if (check_even(i, mid, 0) >= 1) r = mid;
            else l = mid + 1;
        }

        cout << "i = " << i << '\n';
        if (check_even(i, l, check_even(i, l, 0) == 1) == 1) cout << 2 * l;
        else cout << 0;
        cout << '\n';
    }
}
