#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    
    vector<int> a(6);
    for (auto& i : a) cin >> i;

    int t, p;
    cin >> t >> p;
    
    int ans1 = 0, ans2 = 0;
    for (auto& i : a) {
        ans1 += (i + t - 1) / t;
    }
    cout << ans1 << '\n' << n / p << ' ' << n % p;
}
