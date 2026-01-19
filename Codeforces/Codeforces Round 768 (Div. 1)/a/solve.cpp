#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll f(const vector<pii> &ans) {
    ll ret = 0;
    for (auto &[a, b] : ans) ret += a & b;
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // constexpr int t = 10;
    // vector<pii> arr;
    // for (int i = 0; i < (1 << (t - 1)); i++) {
    //     arr.push_back({i * 2, i * 2 + 1});
    // }
    // cout << (1 << (t - 1)) - 2 << " :: " << f(arr) << '\n';
    // swap(arr[0].first, arr[1].first);
    // cout << "1 :: " << f(arr) << '\n';
    // swap(arr[0].first, arr[1].first);

    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;

        if (n == 4 && k == n - 1) {
            cout << -1 << '\n';
            continue;
        }

        vector<pii> ans;
        if (k == n - 1) {
            ans.push_back({n - 2, n - 1});
            ans.push_back({1, 3});
            
            vector<bool> vis(n);
            for (auto &i : ans) vis[i.first] = vis[i.second] = 1;

            int l = 0, r = n - 1;
            while (sz(ans) < n / 2) {
                while (vis[l]) l++;
                while (vis[r]) r--;
                ans.push_back({l, r});
                vis[l] = vis[r] = 1;
            }
        } else {
            for (int i = 0; i < n / 2; i++) {
                ans.push_back({i, n - i - 1});
            }
            for (auto &[a, b] : ans) {
                if (a == k || b == k) {
                    if (a == k) swap(ans[0].first, a);
                    if (b == k) swap(ans[0].first, b);
                    break;
                }
            }
        }

        for (auto &[a, b] : ans) {
            cout << a << ' ' << b << '\n';
        }
        assert(f(ans) == k);
    }
}
