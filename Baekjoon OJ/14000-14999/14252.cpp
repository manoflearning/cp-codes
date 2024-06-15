#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, a[55];

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a, a + n);

    int ans = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (gcd(a[i], a[i + 1]) == 1) continue;

        int res = 3;
        for (int x = a[i] + 1; x <= a[i + 1] - 1; x++) {
            if (gcd(x, a[i]) != 1) continue;
            
            if (gcd(x, a[i + 1]) == 1) { res = 1; break; }

            for (int y = x + 1; y <= a[i + 1] - 1; y++) {
                if (res < 3) break;
                if (gcd(x, y) == 1 && gcd(y, a[i + 1]) == 1) {
                    res = min(res, 2);
                    break;
                }
            }
        }

        ans += res;
    }

    cout << ans;
}