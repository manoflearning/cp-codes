#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll sum = 0, mx = 0;
        for (int i = 0; i < n; i++) {
            sum += max(a[i], a[(i + 1) % n]);
            mx = max(mx, max(a[i], a[(i + 1) % n]));
        }
        cout << sum - mx << '\n';
    }
}