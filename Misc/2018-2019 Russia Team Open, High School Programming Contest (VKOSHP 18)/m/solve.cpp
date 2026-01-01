#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    ll ans = 0, t = 0;
    for(int i = 0; i < n; i++) {
        t++;
        ans = max(ans, t);
        if(i + 1 < n && a[i] == a[i + 1]) t = 0;
    }
    cout << ans << '\n';
}