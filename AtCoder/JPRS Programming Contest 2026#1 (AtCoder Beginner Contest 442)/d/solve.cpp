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

    int n, q;
    cin >> n >> q;

    vector<ll> a(n), ps(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ps[i] = a[i] + (i > 0 ? ps[i - 1] : 0);
    }

    while (q--) {
        int op; cin >> op;

        if (op == 1) {
            int x; cin >> x;
            x--;
            
            ps[x] -= a[x];
            ps[x] += a[x + 1];
            swap(a[x], a[x + 1]);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;

            cout << ps[r] - (l > 0 ? ps[l - 1] : 0) << '\n';
        }
    }

    return 0;
}
