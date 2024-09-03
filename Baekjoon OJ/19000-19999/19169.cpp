#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ll n, k;
    cin >> n >> k;

    if (n == 1 || k == 0) {
        cout << 0;
        return 0;
    }

    assert(1 <= k && k < n);

    vector<pair<ll, ll>> ans;
    ans.push_back({ 0, n - 1 });
    if (0 < k - 1) ans.push_back({ 0, k - 1 });
    if (k < n - 1) ans.push_back({ k, n - 1 });

    if (n <= 100) {
        vector<int> a(n);
        
        iota(a.begin(), a.end(), 0);
        for (auto& i : ans) {
            for (int j = i.first; ; j++) {
                int k = i.second - (j - i.first);
                if (j >= k) break;
                swap(a[j], a[k]);
            }
        }

        for (int i = 0; i < n; i++) {
            assert((a[i] + k) % n == i);
        }
    }

    cout << sz(ans) << '\n';
    for (auto& i : ans)
        cout << i.first << ' ' << i.second << '\n';
}
