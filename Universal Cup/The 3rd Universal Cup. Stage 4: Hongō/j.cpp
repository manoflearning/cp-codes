#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int n;
ll l, r, a[66];

__int128_t f(__int128_t x, int k) {
    if (k == 0) return x == 0;

    vector<__int128_t> ub(k + 1);
    for (int i = 1; i < k; i++) {
        ub[i] = a[i + 1] / a[i] - 1;
    }
    ub[k] = x / a[k];

    if (ub[k] == 0) return f(x, k - 1);

    __int128_t ret = 1;
    for (int i = 1; i < k; i++) {
        ret *= ub[i] / 2 + 1;
    }
    if (ub[k] & 1) {
        ret *= ub[k] / 2 + 1;
        return ret;
    } else {
        ret *= (ub[k] - 1) / 2 + 1;
        return ret + f(x - ub[k] * a[k], k - 1);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> l >> r;
    for (int i = 1; i <= n; i++) cin >> a[i];

    __int128_t ans = r - l + 1 - f(r, n) + f(l - 1, n);
    cout << (ll)ans;
}