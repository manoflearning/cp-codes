#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<ll> a(n);
    for (auto& i : a) cin >> i;

    sort(a.begin(), a.end());
    
    vector<ll> dp(n, INF);

    dp[0] = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (dp[i] == INF) continue;

        int k = i + 1;
        if (a[i + 1] / a[i] == 1) {
            int l = i + 1, r = n - 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (a[mid] / a[i] >= 2) r = mid;
                else l = mid + 1;
            }
            k = l;
            dp[k - 1] = min(dp[k - 1], dp[i] + 1);
        }

        int l = k, r = n - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[mid] / a[i] == a[k] / a[i]) l = mid;
            else r = mid - 1;
        }

        dp[l] = min(dp[l], dp[i] + a[l] / a[i]);
    }

    cout << dp[n - 1];
}