#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;

int n, m, k;
ll a[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    sort(a + 1, a + 1 + n);

    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;

        ll time = 0;
        for (int i = mid; i >= 1; i -= k) {
            time += a[i];
        }

        if (time <= m) l = mid;
        else r = mid - 1;
    }
    cout << l;

    // int ans = 0;
    // ll time = 0;
    // for (int i = k; i <= (n + k - 1) / k * k; i += k) {
    //     int j = min(n, i);

    //     while (time + a[j] > m && j > i - k) j--;

    //     if (j == i - k || time + a[j] > m) break;

    //     ans += j - (i - k);
    //     time += a[j];
    // }

    // cout << ans;
}
