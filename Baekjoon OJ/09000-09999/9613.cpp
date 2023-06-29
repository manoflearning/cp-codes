#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& i : a) cin >> i;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans += gcd(a[i], a[j]);
            }
        }
        cout << ans << '\n';
    }
}
