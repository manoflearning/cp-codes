#include <bits/stdc++.h>
using namespace std;

int n, k;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> k;

        int ans = 1e9;
        ans = min(ans, min(n - k, k) + k);
        ans = min(ans, n + min(n - k, k) + (n - k));
        if (k == n) ans = min(ans, (n + 1) / 2);

        cout << ans << '\n';
    }
}
