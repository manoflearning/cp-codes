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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        if (n & 1) {
            cout << "YES\n";
        } else {
            for (int i = 2; i < n; i++) {
                const ll diff = a[i - 1] - a[i - 2];
                a[i] -= diff, a[i - 1] -= diff;
            }

            cout << (a[n - 2] <= a[n - 1] ? "YES" : "NO") << '\n';
        }
    }
}
