#include <bits/stdc++.h>
using namespace std;

int n, k;
int a[121];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int ans = 0, now = 0;
    for (int i = 1; i <= n; i++)
        if (now + a[i] <= k) {
            now += a[i];
        }
        else {
            now = a[i];
            ans++;
        }

    cout << ans + (now > 0 ? 1 : 0);
}