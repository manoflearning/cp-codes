#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        a.push_back(0);
        sort(all(a));
        a.erase(unique(all(a)), a.end());

        vector<int> dp(sz(a));
        
        // base case
        dp[sz(a) - 1] = 1;
        
        // inductive step
        for (int i = sz(a) - 2; i >= 1; i--) {
            if (a[i - 1] + 1 < a[i]) {
                dp[i] = 1;
            } else {
                dp[i] = !dp[i + 1];
            }
        }
        cout << (dp[1] ? "Alice" : "Bob") << '\n';
    }
}
