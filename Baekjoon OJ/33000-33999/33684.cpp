#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    sort(all(a));

    if (a[n - 1] > k) {
        cout << 0;
        exit(0);
    }
    if (a[0] <= 0) {
        cout << -1;
        exit(0);
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans += (k - a[i]) / a[0];
    }
    ans++;
    
    cout << ans;
}
