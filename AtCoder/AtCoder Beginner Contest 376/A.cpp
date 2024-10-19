#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, c;
    cin >> n >> c;

    int ans = 0;
    int prv = -1e9;
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        if (prv + c <= t) ans++, prv = t;
    }

    cout << ans;
}
