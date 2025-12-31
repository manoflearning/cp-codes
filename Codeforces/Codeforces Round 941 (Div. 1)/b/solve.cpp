#pragma GCC optimize("Ofast")
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
        int n, k;
        cin >> n >> k;

        vector<int> ans;
        
        int t = 0;
        while ((1 << t) <= k) t++;
        t--;

        for (int i = 0; i <= 19; i++) {
            if (i != t) ans.push_back(1 << i);
        }
        ans.push_back(k - (1 << t));
        ans.push_back(k + 1);
        ans.push_back(k + 1 + (1 << t));

        cout << sz(ans) << '\n';
        for (auto &i : ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
