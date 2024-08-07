#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
ll a[101010];
ll dp1mx[101010], dp2mx[101010];
ll dp1mn[101010], dp2mn[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        dp1mx[i] = max(a[i], a[i] + dp1mx[i - 1]);
        dp1mn[i] = min(a[i], a[i] + dp1mn[i - 1]);
    }
    for (int i = n; i >= 1; i--) {
        dp2mx[i] = max(a[i], a[i] + dp2mx[i + 1]);
        dp2mn[i] = min(a[i], a[i] + dp2mn[i + 1]);
    }

    ll ans = 0;
    for (int i = 1; i + 1 <= n; i++) {
        ans = max(ans, dp1mx[i] - dp2mn[i + 1]);
        ans = max(ans, dp2mx[i + 1] - dp1mn[i]);
    }

    cout << ans;
}