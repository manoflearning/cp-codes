#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;
        vector<int> cnt2(n), cnt5(n);
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            while (x % 2 == 0) cnt2[i]++, x /= 2;
            while (x % 5 == 0) cnt5[i]++, x /= 5;
        }
        vector<int> dp2(n), dp5(n);
        dp2[0] = cnt2[0], dp5[0] = cnt5[0];
        for (int i = 1; i < n; i++) {
            dp2[i] = dp5[i] = 1e9;
            for (int j = i - 1; j >= max(0, i - k); j--) {
                dp2[i] = min(dp2[i], cnt2[i] + dp2[j]);
                dp5[i] = min(dp5[i], cnt5[i] + dp5[j]);
            }
        }
        cout << min(dp2[n - 1], dp5[n - 1]) << '\n';
    }
}