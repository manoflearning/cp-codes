#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    if(n == 2) return 0;
    
    sort(a.begin(), a.end());
    return min(a[n - 1] - a[1], a[n - 2] - a[0]);
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cout << solve() << '\n';
    }
}
