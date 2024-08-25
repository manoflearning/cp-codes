#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        long long n; cin >> n;
        if (n & 1) cout << -1 << '\n';
        else cout << n / 2 << ' ' << (1ll << 60) - n / 2 << '\n';
    }
}